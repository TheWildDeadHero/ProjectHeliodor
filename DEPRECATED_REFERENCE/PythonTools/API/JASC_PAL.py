"""
@package        PyPNGTools
@file           JASC_PAL.py

@description    This module coontains functionality for reading from and writing to
                JASC-PAL files. JASC-PAL files are plaintext files with the .PAL
                extensioon that contain the minimum amount of information needed for
                a palette and are of the following format:

                <FORMAT NAME>                   // Always JASC-PAL
                <FILE VERSION>                  // Typically starts at 0100
                <NUMBER OF COLORS IN FILE>      // Either 16 or 256
                <...R G B tuples...>            // Palette data

                This module also intruduces some extensions that may be useful for
                programmers using the regular format. Extended JASC-PAL (referred
                to as JASC-PAL-EXT henceforth) allows the use of flexible palette
                sizes, alpha values, RGB(A) modes, and allows the assignment of a
                transparency color. JASC-PAL-EXT files follow the format below:

                <FORMAT NAME>                   // Always JASC-PAL-EXT
                <FILE VERSION>                  // Typically starts at 0100
                <NUMBER OF COLORS IN FILE>      // Any number greater than 0
                <TRANSPARENT COLOR>             // Index of transparent color in
                                                   file; -1 if no color is
                                                   transparent.
                <BITS PER SUBPIXEL>             // The number of bits per subpixel,
                                                   usually 8 but may be fewer for
                                                   systems with less power. This
                                                   entry does not allow for
                                                   asymmetric formats like RGB565.
                <ALPHA>                         // "ALPHA" if alpha is used,
                                                   "NO ALPHA if alpha is not used
                <... R G B A tuples...>         // Palette data; Alpha value always
                                                   0 for files that don't use alpha

                This module also follows the color tuple scheme as implemented in
                the PyPNG module to allow for relatively seamless integration. As
                a result, whenever this module deals with RGB(A) data, it is stored
                as a 3-tuple for regular RGB or as a 4-tuple for RGB with alpha.
                As a result, RGB(A) tuples look like what is shown below:

                (Red, Green, Blue, Alpha*)

                *When used.

@author         William Smith
@copyright      2024
"""

"""
-----[ Imports
"""

from typing import *
from io import TextIOWrapper, _WrappedBuffer
from enum import StrEnum
from copy import deepcopy

from API.Color import *

"""
-----[ Constants
"""

"""
-----[ Enums
"""

"""
@enum           JASCFormat

@description    Simple String Enum for JASC formats
"""
class JASCFormat(StrEnum):
    STD                     = "JASC-PAL"
    EXT                     = "JASC-PAL-EXT"

"""
@enum           AlphaVal

@description    Simple String Enum for alpha/no alpha strings
"""
class AlphaVal(StrEnum):
    USED                    = "ALPHA"
    UNUSED                  = "NO_ALPHA"

"""
@enum           HeaderEntries

@description    String enum that contains all possible parameters
                for a JASC header
"""
class HeaderEntries(StrEnum):
    FORMAT                  = "format"
    FILE_VERSION            = "file_version"
    NUM_COLORS              = "num_colors"
    TRANSPARENCY            = "transparency"
    COLOR_DEPTH_BITS        = "color_depth_bits"
    ALPHA                   = "alpha"

"""
-----[ Classes
"""

"""
@class          An dummy exception class specifically for JASC-PAL standard
                violations. The lack of implementation is intentional. 
"""
class ProtocolError(Exception):
    pass

"""
-----[ Collections
"""

# NONE

"""
-----[ Struct Templates
"""

_STD_HEADER_INFO_TEMPLATE   = {
    HeaderEntries.FORMAT:           "",
    HeaderEntries.FILE_VERSION:     "0100",
    HeaderEntries.NUM_COLORS:       16
}

_EXT_HEADER_INFO_TEMPLATE   = {
    HeaderEntries.FORMAT:           "",
    HeaderEntries.FILE_VERSION:     "0100",
    HeaderEntries.NUM_COLORS:       0,
    HeaderEntries.TRANSPARENCY:     -1,
    HeaderEntries.COLOR_DEPTH_BITS: 8,
    HeaderEntries.ALPHA:            AlphaVal.UNUSED
}

"""
-----[ Internal Functions
"""

"""
@description    A helper function that parses the header information.

                Header information is stored in an information dictionary, with the
                following format:
                
                "format"                // The format line of the file
                "version"               // The version line of the file
                "num_colors"            // The color count line of the file

                The following entries can only be found in extended versions of the
                JASC-PAL format.

                "transparency"          // The index of the color for transparency
                "bit_color"             // The number of bits used for subpixels
                "alpha"                 // Either True or False; if alpha is used

@see            JASC-PAL specification at the top of this file.

@param[in]      line_data - A list of unprocessed lines from the file. The line data
@return         Dictionary containing the parsed header information
"""
def _parse_header(line_data: list[str]) -> dict:
    info    = {HeaderEntries.FORMAT:            "",
               HeaderEntries.FILE_VERSION:      "",
               HeaderEntries.NUM_COLORS:        0}

    # Check the formt
    info[HeaderEntries.FORMAT]  = line_data.pop(0).strip('\n')

    if info[HeaderEntries.FORMAT] not in (JASCFormat.STD, JASCFormat.EXT):
        raise ProtocolError("Valid format not defined.")

    # File version should ideally be an int, but not going to check that.
    info[HeaderEntries.FILE_VERSION]  = line_data.pop(0).strip('\n')

    # Check the number of colors and ensure at least one exists for extended
    # files or that the number is 16 or 256 for standard files.
    info[HeaderEntries.NUM_COLORS] = int(line_data.pop(0), base=10)

    if info['format'] == JASCFormat.STD and info['num_colors'] not in (16, 256):
        raise ProtocolError("Standard JASC-PAL files may only have 16 or 256 colors.")
    elif info['format'] == JASCFormat.EXT and info['num_colors'] < 1:
        raise ProtocolError("Extended JASC-PAL files must have at least one color.")

    # Extended JASC-PAL contains some additional data in the header, so parse it.
    if info[HeaderEntries.FORMAT] == JASCFormat.EXT:

        # Check to make sure the index of the transparent color maps to a valid
        # color.
        info[HeaderEntries.TRANSPARENCY] = int(line_data.pop(0), base=10)

        if info[HeaderEntries.TRANSPARENCY] > info[HeaderEntries.NUM_COLORS]                       \
            or info[HeaderEntries.TRANSPARENCY] < -1:
            raise ProtocolError("Transparency index outside of valid range.")

        # Check to make sure at least one bit exists for each folor and that each
        # color is not represented by more than 8 bits.
        #
        # @todo Explore deep color support
        info[HeaderEntries.COLOR_DEPTH_BITS] = int(line_data.pop(0), base=10)

        if info[HeaderEntries.COLOR_DEPTH_BITS] < 3:
            raise ProtocolError("Subpixels must have at least one bit per color representation.")
        elif info[HeaderEntries.COLOR_DEPTH_BITS] > 32:
            raise ProtocolError("Only color depths up to True Color with alpha are supported.")
        elif info[HeaderEntries.COLOR_DEPTH_BITS] % 3 > 0 and info[HeaderEntries.ALPHA] == AlphaVal.USED:
            raise ProtocolError("Invalid RGB bit depth. Must be a value divisible by 3 (for each subpixel).")
        elif info[HeaderEntries.COLOR_DEPTH_BITS] % 4 > 0 and info[HeaderEntries.ALPHA] == AlphaVal.UNUSED:
            raise ProtocolError("Invalid RGBA bit depth. Must be a value divisible by 4 (for each subpixel and alpha).")

        # Check to make sure the alpha entry is one of the two valid choices.
        info[HeaderEntries.ALPHA] = line_data.pop(0).strip('\n')

        if info[HeaderEntries.ALPHA] not in (AlphaVal.USED, AlphaVal.UNUSED):
            raise ProtocolError("Invalid alpha entry.")
        
    return info

"""
@description    Helper function that parses through the actual data lines in
                a JASC-PAL file. Checks to make sure the data integrity is good
                before returning to said data.

@param[in]      line_data - A list of all lines read from the file
@return         The palette data as a list of RGB(A) tuples
"""
def _parse_body(line_data: list[str]) -> list[tuple]:
    palette = []

    # Remove header information if present.
    if line_data[0] == JASCFormat.STD:
        del line_data[0:3]
    elif line_data[0] == JASCFormat.EXT:
        del line_data[0:6]

    # Since the file is loaded in lines, iterate through each line. Attempt to convert the character to a numeric value
    # and then store the tuple in the palette list.
    for index in range(len(line_data)):
        line = tuple(line_data.pop(0).strip('\n').split(' '))

        # Each line is expected to decompose to either 3-tuples or 4-tuples. If this doesn't occur, raise.
        if len(line) < 3 or len(line) > 4:
            raise ProtocolError(f"Line {index} does not contain a valid color tuple.")

        # Convert each individual color/value in the tuple to an integer.
        for color_index, color in enumerate(line):
            if index == RGBIndex.RED:
                which_color = Color.RED
            elif index == RGBIndex.GREEN:
                which_color = Color.GREEN
            elif index == RGBIndex.BLUE:
                which_color = Color.BLUE
            elif index == RGBIndex.ALPHA:
                which_color = "alpha"

            try:
                line[color_index] = int(color, base=10)

                # Values are expected to be between 0 and 255 for True Color (the maximum supported color depth). If any
                # resolve larger, raise.
                if not 0 <= line[color_index] <= 255:
                    raise ValueError(f"Line {index}, {which_color} is not in range. Expected [0,255], got {line[color_index]}")

            except:
                # In this instance, the provided value cannot be converted into an integer. Likely because it's not a
                # numeric entry.
                raise ProtocolError(f"Line {index}, {which_color} does not contain a valid value.")
            
        # The color tuple has passed all checks, so add to the list.
        palette.append(line)
    
    return palette

"""
@description    Checks to make sure the info dictionary follows protocol standards. Raises
                whenever there is an entry that does not conform or have a valid value.

@see            JASC-PAL specification at the top of this file.

@param[in]      info_dict - A dictionary containing all the header information.
@return         None
"""
def _check_header(info_dict: dict) -> None:

    if HeaderEntries.FORMAT not in info_dict.keys():
        raise KeyError(f"Expected a \"{HeaderEntries.FORMAT}\" entry. None found.")
    
    if HeaderEntries.FILE_VERSION not in info_dict.keys():
        raise KeyError(f"Expected a \"{HeaderEntries.FILE_VERSION}\" entry. None found.")
    
    if HeaderEntries.NUM_COLORS not in info_dict.keys():
        raise KeyError(f"Expected a \"{HeaderEntries.NUM_COLORS}\" entry. None found.")
    
    if info_dict[HeaderEntries.FORMAT] == JASCFormat.EXT:
        if info_dict[HeaderEntries.NUM_COLORS] < 1:
            raise ProtocolError("Palette size expected to have a size of at least 1.")
        
        if info_dict[HeaderEntries.TRANSPARENCY] not in range(-1, info_dict[HeaderEntries.NUM_COLORS]):
            raise ProtocolError("Transparency index not in a valid range.")
        
        if info_dict[HeaderEntries.COLOR_DEPTH_BITS] not in range(1, 9):
            raise ProtocolError("Color depth invalid. Must be at least 1 bit and at most 8 bits per subpixel")
        
        if info_dict[HeaderEntries.ALPHA] not in (AlphaVal.USED, AlphaVal.UNUSED):
            raise ProtocolError(f"Invalid alpha entry. Must be \"{AlphaVal.USED}\" or \"{AlphaVal.UNUSED}\".")
        
    elif info_dict[HeaderEntries.FORMAT] != JASCFormat.STD:
        raise ProtocolError(f"Expected either {JASCFormat.STD} or {JASCFormat.EXT} for format. Got {info_dict[HeaderEntries.FORMAT]}.")

    elif info_dict[HeaderEntries.NUM_COLORS] not in (16, 256):
        raise ProtocolError("Invalid number of colors provided.")

"""
@description    Checks to make sure all provided RGB(A) tuples follow
                the protocoal. Tuples need to be either 3-tuples or
                4-tuples, and each tuple entry must be in range of
                0 inclusive to 256 exclusive.

                This function raises if any entry is out of specification.

@param[in]      rgb_tuples - A list of the RGB(A) tuples to check
"""
def _check_body(rgb_tuples: list[tuple]) -> None:
    
    for index, color in enumerate(rgb_tuples):

        if len(color) not in range(3, 5):
            raise ProtocolError("RGB(A) tuples must have at least 3 entries and at most 4.")
        
        if color[RGBIndex.RED] not in range(256):
            raise ValueError(f"Red value at line {index} not in range.")
        elif color[RGBIndex.GREEN] not in range(256):
            raise ValueError(f"Green value at line {index} not in range.")
        elif color[RGBIndex.BLUE] not in range(256):
            raise ValueError(f"Blue value at line {index} not in range.")
        elif len(color) == 4 and color[RGBIndex.ALPHA] not in range (256):
            raise ValueError(f"Alpha value at line {index} not in range.")

"""
@description    A helper function that takes loaded file and parses the
                info. Uses helper functions to seperately parse the header
                and the body. Before returning the data, this function
                also makes sure that unneeded data is removed (for
                example, if alpha values are included but not used) and
                that RGB tuples follow the standard protocol.

@param[in]      file - A wrapped buffer containing the opened file
@return         A 2-tuple containing a list of all colors in the palette and the
                info dictionary.
"""
def _load_from_file(file: TextIOWrapper[_WrappedBuffer]) -> list[tuple]:

    data        = file.readlines()

    info        = _parse_header(data)
    palette     = _parse_body(data)

    if len(palette) != info[HeaderEntries.NUM_COLORS]:
        raise ProtocolError("Number of colors does not match header data.")
    
    for index, color in enumerate(palette):
        
        # Make sure the data and expected format match.
        if len(color) > 3 and info[HeaderEntries.FORMAT] == JASCFormat.STD:
            raise ProtocolError("Alpha values provided, but standard JASC-PAL RGB tuple expected.")
        
        # In the case alpha is not used, but alpha values are provided, remove them from the tuple.
        elif len(color) == 4 and info[HeaderEntries.ALPHA] == AlphaVal.UNUSED:
            palette[index] = tuple(color[0:2])
    
    return palette, info

"""
@description    A wrapper function that opens the file from the given path and
                then calls the load_from_file helper function.

@see            _load_from_file() documentation

@param[in]      filename - a path to the desired file to load from
@return 
"""
def _load_from_file_path(filename: str) -> list[tuple]:
    palette     = None
    info        = None

    # Keep the file open only for as long as we need.
    with open(filename, 'r') as file:
        palette, info = _load_from_file(file)

    return palette, info

"""
-----[ API Functions (Externally-available functions)
"""

"""
@description    Takes either a file buffer or a file path and attempts to
                load the palette and header information. Note that this
                function will raise if there are any issues in the palette
                file.

@param[in]      file - Either a file buffer or file path
@return         A 2-tuple containing the palette and header info
"""
def load(file: Union[TextIOWrapper[_WrappedBuffer], str]) -> tuple[list, dict]:
    # Assume a file path if "file" is a string.
    if isinstance(file, str):
        data, info = _load_from_file_path(file)

    # In all other instances, assume the argument is a file bit stream. If it's not,
    # the function will fail in a descriptive way.
    else:
        data, info = _load_from_file(file)

    return data, info

"""
@description    Takes RGB tuple data and writes it to a JASC-PAL or a
                JASC-PAL-EXT file, depending on which format is specified.
                If anything is not compliant with the JASC-PAL standard
                or the extended version, this function will raise.

@param[in]      rgb_tuples - A list of RGB(A) values to write. Alpha should
                only be included in EXT-formatted files.
@param[in]      filename - Either an opened file buffer or a file path string
@param[in]      format - Which JASC-PAL format to use [default="JASC-PAL"]
"""
def save(rgb_tuples: list[tuple],
         file: Union[TextIOWrapper[_WrappedBuffer], str],
         format: str = JASCFormat.STD,
         version: Union[str, int] = "0100",
         num_colors: int = 16,
         transparency: int = -1,
         color_depth: ColorDepth = ColorDepth.RGB888,
         alpha: str = AlphaVal.UNUSED) -> None:
    
    file_text = ""
    
    header = {
        HeaderEntries.FORMAT:          format,
        HeaderEntries.FILE_VERSION:    version,
        HeaderEntries.NUM_COLORS:      num_colors
    }

    if format == JASCFormat.EXT:
        header[HeaderEntries.TRANSPARENCY]     = transparency
        header[HeaderEntries.COLOR_DEPTH_BITS] = color_depth
        header[HeaderEntries.ALPHA]            = alpha
    
    _check_header(header)
    _check_body(rgb_tuples)

    if len(rgb_tuples) != num_colors:
        raise ProtocolError("Number of colors provided does not match the expected number of colors.")

    file_text += format                 + '\n'
    file_text += str(version)           + '\n'
    file_text += str(num_colors)        + '\n'

    if format == JASCFormat.EXT:
        file_text += str(transparency)  + '\n'
        file_text += str(color_depth)   + '\n'
        file_text += alpha              + '\n'

    for color in rgb_tuples:

        if len(color) == 4 and format == JASCFormat.STD:
            raise ValueError("JASC-PAL standard protocol used. Expected tuple with length of 3, but received 4.")
        elif len(color) == 3 and format == JASCFormat.EXT:
            color = tuple(list(color).append(0))

        tuple_string = ""

        for subpixel in color:
            tuple_string += f"{str(subpixel)} "

        file_text += tuple_string[:-1] + '\n'

    # If a file path is given, open the file, write it, and then close it.
    if isinstance(file, str):

        with open(file, "w+", encoding='utf8') as file:
            file.write(file_text[:-1])
            file.flush()

    # If a bit stream is proovided, just write and assume it'll be properly closed later.
    else:
        file.write(file_text[:-1])
        file.flush()

"""
@description    Creates a copy of the standard header dictionary and returns
                it.

@return         A copy of the standard protocol header dictionary
"""
def standard_header_info() -> dict:
    return deepcopy(_STD_HEADER_INFO_TEMPLATE)

"""
@description    Creates a copy of the extended header dictionary and returns
                it.

@return         A copy of the extended header protocol dictionary
"""
def extended_header_info() -> dict:
    return deepcopy(_EXT_HEADER_INFO_TEMPLATE)


"""
@description    All elements of the API to include when including via *
"""
__all__ = [JASCFormat, AlphaVal, HeaderEntries, ProtocolError, load, save, standard_header_info, extended_header_info, ColorDepth]