"""
@package        PyPNGTools
@file           ImageOps.py

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
System Imports
"""
from typing import *

from enum import StrEnum, IntEnum
from io import TextIOWrapper, _WrappedBuffer

import png
import copy
import os
"""
Virtual Environment Imports
"""
import png

"""
Module Imports
"""
import API.Color as Color
import API.JASC_PAL as JASC_PAL

"""
@note           Windows and Unix systems handle new lines in encoded text and directories differently.
"""
import API.Platform

"""
"""
def _load_palette_from_image(file: Union[TextIOWrapper[_WrappedBuffer], str], color_depth: Color.ColorDepth = Color.ColorDepth.RGB888) -> list:

    if isinstance(file, str):
        file = open(file, 'r')
        close_file = True
    else:
        close_file = False

    image = png.Reader(file = file)
    image.read()

    palette = []

    # PLTe chunk is optional for color modes other than 3. Try to pull palette data
    # but if it's not possible, scan the image for unique palette tuples.
    try:
        palette = image.palette()

    except png.ProtocolError or png.ChunkError:
        if color_depth == Color.ColorDepth.RGBA8888:
            as_rgb = image.asRGBA8
        elif color_depth == Color.ColorDepth.RGB888:
            as_rgb = image.asRGB8
        elif color_depth in Color._RGB_DEPTHS_WITH_ALPHA and color_depth != Color.ColorDepth.GREYSCALE_ALPHA:
            as_rgb = image.asRGBA
        elif color_depth in (Color.ColorDepth.GREYSCALE, Color.ColorDepth.GREYSCALE_ALPHA):
            as_rgb = image.asDirect
        else:
            as_rgb = image.asRGB
        
        _, _, row_data, _ = as_rgb()

        for row in row_data:
            for color in row:
                if color not in palette:
                    palette.append(color)

    if close_file:
        file.close()

    return palette

"""
@description    Function that loads a palette from a given source. Expects only
                one of the following arguments. Returns a list of RGB tuples.

@param[in]      file - Loads a palette from a .pal file buffer already open and
                loaded.
@param[in]      filename - Loads a palette from the provided .pal file path
@param[in]      png - Loads a palette from a given image. If indexed, the palette
                is loaded directly. If not indexed, the file is read by pixel,
                each unique color tuple being stored in a list and then returned.
@return         List of RGB(A) tuples
"""
def load_palette(file: Union[TextIOWrapper[_WrappedBuffer], str], color_depth: Color.ColorDepth = Color.ColorDepth.RGB888, png: bool = False) -> list[tuple]:

    if png:
        palette = _load_palette_from_image(file, color_depth)
    else:
        palette, _ = JASC_PAL.load(file)    # Returns a tuple including a header file that isn't used here.
    
    return palette

"""
@description    Convenience wrapper function that opens a PNG image and returns
                the RGB/Info tuple.

@param[in]      The file to open. May be a path or a bitstream.
@return         The image data
"""
def load_image(file: Union[TextIOWrapper[_WrappedBuffer], str]) -> tuple:
    if isinstance(file, str):
        file = open(file, 'r')
        close_file = True
    else:
        close_file = False

    try:
        image = png.Reader(file=file).read()
    except Exception as e:
        image = (None, None, None, e)

    if close_file:
        file.close()

    return image

"""
@description    Convenience wrapper function that writes a PNG mage to a file.

@param[in]      file - Either the file path or an open file bitstream
@param[in]      width - The width of the image in pixels
@param[in]      height - The height of the image in pixels
@param[in]      data - A list of indices that map to the palette
@param[in]      palette - The list of RGB(A) tuples used
@param[in]      bitdepth - The color depth in terms of bits used for a single color
@return         None
"""
def write_image(file: Union[TextIOWrapper[_WrappedBuffer]], width: int, height: int, data: list, palette: list, bitdepth: int = 8, **kwargs) -> None:
    if isinstance(file, str):
        file = open(file, 'wb+')
        close_file = True
    else:
        close_file = False

    png.Writer(width=width, height=height, palette=palette, bitdepth=bitdepth, **kwargs).write(file, data)

    if close_file:
        file.close()

"""
@description    Convenience function that wraps around the walk() from from the OS
                package. Iterates through all directories produced and looks for
                files with the given extension. Ignores hidden files (with leading
                period) and subdirectories by default, but can look for and in those.

@param[in]      path - The directory to start looking in
@param[in]      file_ext - The file extension to look for
"""
def scrape_for_files(path: str, file_ext: Union[list, tuple, str], check_sub_dir: bool = False, ignore_hidden: bool = True) -> list:
    found_files = list()

    if isinstance(file_ext, str):
        file_ext = [file_ext]

    root = None

    # Just add a separator if it doesn't exist
    if "." != file_ext[0]:
        file_ext = "." + file_ext

    for parent, directories, files in os.walk(path):

        # Do some checking here to make sure we only check the current directory and not any subdirectories
        if root is None:
            root = parent
        elif parent != root and not check_sub_dir:
            break

        for file in files:
            if (file[-(len(file_ext)):] in file_ext) and ("." != file[0] or not ignore_hidden):
                found_files.append(os.path.join(parent, file))

    return found_files

"""
@description    Iterates through every color in the provided palette and converts each
                RGB(A) tuple to the new depth/provided range. RGB(A) tuples being
                converted to a lower bit depth with result in some data loss.

@param[in]      palette - The list of color tuples to convert
@param[in]      old_depth - The original color depth
@param[in]      new_depth - The new color depth to convert to
@param[in]      
"""
def rescale_rgb_palette(palette: list,
                        old_depth: Color.ColorDepth,
                        new_depth: Color.ColorDepth, 
                        old_offset: bool = False,
                        new_offset: bool = False) -> list:

    new_palette = []

    for color in palette:
        new_palette.append(Color.rescale_color(color, old_depth, new_depth, old_offset, new_offset))

    return new_palette

# Iterates through the list of files and corrects the palettes.
def fix_palette(files: list,
                file_prefix: str = "_FIXED",
                format: Color.ColorDepth = Color.ColorDepth.RGB555,
                source_format: int = Color.ColorDepth.RGB888) -> int:

    number_palettes_fixed = 0

    for file in files:
        height, width, bitmap, info = load_image(file)
        palette = rescale_rgb_palette(load_palette(file), source_format, format, new_offset = True) # Offset the new format by one to prevent invalid values
        palette = rescale_rgb_palette(palette, source_format, format)

        new_path, file_ext = file.rsplit(".", 1)

        new_path = new_path + file_prefix + "." + file_ext 

        write_image(new_path, height, width, bitmap, palette)

        number_palettes_fixed += 1

    return number_palettes_fixed

#
def paint_palettes_to_images(images: list, palettes: list) -> int:

    files_written = dict()
    num_images_converted = 0

    for image_path in images:

        for palette_path in palettes:
            width, height, data, _ = load_image(image_path)

            image_dir, image_file = str(image_path).rsplit(API.Platform.DIR_DELIMITER, 1)
            image_filename, image_extension = str(image_file).rsplit(".", 1)

            if data is None:
                print("Could not load image.\n")
                continue

            else:
                try:
                    palette = load_palette(palette_path)
                except:
                    print("Could not load palette.\n")
                    continue

                palette_name, _ = str(palette_path).rsplit('.', 1)

                output_file = os.path.join(image_dir, f"{image_filename}_{palette_name}.{image_extension}")

                if output_file not in files_written.keys():
                    files_written[output_file] = 0
                else:
                    files_written[output_file] += 1
                    output_file = os.path.join(image_dir, f"{image_filename}_{palette_name}_{files_written[output_file]}.{image_extension}")

                try:
                    write_image(output_file, width, height, data, palette)
                    num_images_converted += 1

                except:
                    print("Could not write file.\n")
                    continue

    return num_images_converted

#
def find_num_colors_from_rows(source: Union[list[tuple], TextIOWrapper[_WrappedBuffer], str]) -> int:

    if isinstance(source, list):
        rows = source
        
    else:
        _, _, rows, _ = load_image(source)

    colors = []

    for row in rows:
        for color in row:
            if color not in colors:
                colors.append(color)

    return len(colors)

def apply_to_background(row_data: list, alpha: int, background_color: Union[int, list, tuple]) -> tuple:
    return 0, 0, [], None

def reduce_palette(palette: list[tuple[int, int, int]]) -> list[tuple[int, int, int]]:
    ...