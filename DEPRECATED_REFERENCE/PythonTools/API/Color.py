"""
@package        PyPNGTools
@file           Color.py

@description    This module primarily deals with color-related operations. Colors
                are traditionally represented as Red, Green, and Blue on computers,
                with alpha sometimes being used to blend a "forward" and "backward"
                color. Different systems are capable of different depths of color 
                (to be more specific, the number of bits used to represent colors).
                Enums are used for easy labeling and defining valid numbers of bits
                used.

@note           This module currently does not support deep color (such as HDR10+)
                modes.

@author         William Smith
@copyright      2024
"""

"""
-----[ Imports
"""
from typing import *

from enum import StrEnum, IntEnum, auto
from sys import stderr

"""
-----[ Constants
"""

# NONE

"""
-----[ Enums
"""

"""
@enum           Color

@description    An enumeration of color names specifically divided for enough
                resolution for categorizing.
"""
class Color(StrEnum):
    # Neutrals
    BLACK           =   "black"
    GREY            =   "grey"
    WHITE           =   "white"

    # Colors
    RED             =   "red"
    ORANGE          =   "orange"
    YELLOW          =   "yellow"
    CHARTREUSE      =   "chartreuse"
    GREEN           =   "green"
    TEAL            =   "teal"
    CYAN            =   "cyan"
    AZURE           =   "azure"
    BLUE            =   "blue"
    PURPLE          =   "purple"
    MAGENTA         =   "magenta"
    PINK            =   "pink"

"""
@enum           ColorDepth

@description    Used for keeping track of valid color depths. The total amunt of bits
                is used for each entry, excepting greyscale and greyscale with alpha.
                For example, RGB222 has a value of 6, as 6 bits are used to represent
                the whole color without alpha (2 bits for red, 2 bits for green, and
                2 bits for blue)
"""
class ColorDepth(IntEnum):
    # Equally-scaled color depths
    GREYSCALE       =   0
    GREYSCALE_ALPHA =   1
    RGB111          =   3
    RGBA1111        =   4
    RGB222          =   6
    RGBA2222        =   8
    RGB333          =   9
    RGBA3333        =   12
    RGB444          =   12
    RGBA4444        =   16
    RGB555          =   15
    RGBA5555        =   20
    RGB666          =   18
    RGBA6666        =   24
    RGB777          =   21
    RGBA7777        =   28
    RGB888          =   24
    RGBA8888        =   32

    # Full-byte color depths - R, G, and B values are not equal in an effort to use
    # every available bit in all used bytes.
    RGB233          =   8
    RGB332          =   8
    RGB565          =   16

"""
@enum           RGBIndex

@description    The indicies for red, green, blue, and alpha in the RGB(A) tuple    
"""
class RGBIndex(IntEnum):
    RED             =   0
    GREEN           =   1
    BLUE            =   2
    ALPHA           =   3

"""
-----[ Classes
"""

# NONE

"""
-----[ Collections
"""

"""
@description    The color depths that use all available bits
"""
_FULL_BYTE_RGB_DEPTHS   = (ColorDepth.RGB233,
                           ColorDepth.RGB332,
                           ColorDepth.RGB565)

"""
@description    All RGB depths that do not use alpha and are not deep color/HDR
"""
_RGB_DEPTHS             = (ColorDepth.RGB111,
                           ColorDepth.RGB222,
                           ColorDepth.RGB333,
                           ColorDepth.RGB444,
                           ColorDepth.RGB555,
                           ColorDepth.RGB666,
                           ColorDepth.RGB777,
                           ColorDepth.RGB888)

"""
@description    All RGB depths that use alpha.
"""
_RGB_DEPTHS_WITH_ALPHA  = (ColorDepth.RGBA1111,
                           ColorDepth.RGBA2222,
                           ColorDepth.RGBA3333,
                           ColorDepth.RGBA4444,
                           ColorDepth.RGBA5555,
                           ColorDepth.RGBA6666,
                           ColorDepth.RGBA7777,
                           ColorDepth.RGBA8888)

"""
@description    All colors that are considered neutral (ie. they don't have a strong tint
                to any red, green blue, etc. color.)
"""
_NEUTRAL_COLORS         = (Color.BLACK,
                           Color.GREY,
                           Color.WHITE)

"""
@description    A dictionary of colors that are similar/related to the provided color.
"""
_COLOR_RELATIVES = {
    Color.RED:          (Color.RED,         Color.PINK,         Color.ORANGE),
    Color.PINK:         (Color.PINK,        Color.MAGENTA,      Color.RED),
    Color.MAGENTA:      (Color.MAGENTA,     Color.PURPLE,       Color.PINK),
    Color.PURPLE:       (Color.PURPLE,      Color.BLUE,         Color.MAGENTA),
    Color.BLUE:         (Color.BLUE,        Color.AZURE,        Color.PURPLE),
    Color.AZURE:        (Color.AZURE,       Color.CYAN,         Color.BLUE),
    Color.CYAN:         (Color.CYAN,        Color.TEAL,         Color.AZURE),
    Color.TEAL:         (Color.TEAL,        Color.GREEN,        Color.CYAN),
    Color.GREEN:        (Color.GREEN,       Color.CHARTREUSE,   Color.TEAL),
    Color.CHARTREUSE:   (Color.CHARTREUSE,  Color.YELLOW,       Color.GREEN),
    Color.YELLOW:       (Color.YELLOW,      Color.ORANGE,       Color.CHARTREUSE),
    Color.ORANGE:       (Color.ORANGE,      Color.RED,          Color.YELLOW)
}

"""
-----[ Struct Templates
"""

# NONE

"""
-----[ Internal Functions
"""

"""
@description    Calculates the average difference of all subpixel values for two color tuples.

@param[in]      rgb_left - The first RGB tuple to use
@param[in]      rgb_right - the second RGB tuple to use
@return         The average difference
"""
def _get_avg_diff(rgb_left: tuple[int, int, int], rgb_right: tuple[int, int, int]) -> int:
    r_diff = abs(rgb_left[RGBIndex.RED]    - rgb_right[RGBIndex.RED])
    g_diff = abs(rgb_left[RGBIndex.GREEN]  - rgb_right[RGBIndex.GREEN]) 
    b_diff = abs(rgb_left[RGBIndex.BLUE]   - rgb_right[RGBIndex.BLUE])

    return (r_diff + g_diff + b_diff) / 3

"""
-----[ API Functions (Externally-available functions)
"""

"""
@description    Takes a num of bits for a single color and converts it into
                a valid bit depth. If alpha is used, the number of bits is
                multiplied by 4 (n bits for R, G, B, and A). If not, the
                number of bits is multipliued by 3. Also determines the
                number of additional bits needed for byte-filled depths.

@param[in]      num_bits - The number of bits used for a single color in
                an RGB(A) tuple
@param[in]      alpha - True if alpha is used
@param[in]      fill_byte - 

"""
def convert_to_total_bits(num_bits: int, alpha: bool, fill_byte: bool) -> int:

    if alpha:
        num_bits *= 4 
    else:
        num_bits *= 3

    # Some color depths usually try to use every bit in all needed bytes. So add the remainder.
    if fill_byte:
        remainder = color_bits % 8

        # If the remainder is more than half of a byte: Assume we're adding bits to a color. Else, assume
        # subtraction.
        color_bits = color_bits + ((-1 if remainder < 4 else 1) * (color_bits % 8))

    return num_bits

"""
@description    Checks to see if the color depth provided uses all available
                bits, resulting in an uneven value distribution.

@return         True if the color depth is RGB565, RGB233, or RGB332
"""
def uses_all_bits(color_depth: ColorDepth) -> bool:
    return color_depth in _FULL_BYTE_RGB_DEPTHS

"""
@description    Checks the number of bits (as well as alpha and whether all bits
                are used) to see if they form a valid depth.

@param[in]      num_bits - The number of bits in a single sub-color (RGB)
@param[in]      alpha - True if alpha is used
@param[in]      fill_byte - True if all bits are used in all used bytes
@return         True if the depth is valid
"""
def is_valid(num_bits: int, alpha: bool = False, fill_byte: bool = False) -> bool:

    if num_bits > 0:
        num_bits = convert_to_total_bits(num_bits, alpha, fill_byte)
    elif alpha:
        num_bits = 1
    elif num_bits < 0:
        raise ValueError("Color depth cannot be less than 0 bits")

    return num_bits in _FULL_BYTE_RGB_DEPTHS      \
            or num_bits in _RGB_DEPTHS          \
            or num_bits in _RGB_DEPTHS_WITH_ALPHA   \
            or num_bits in (ColorDepth.GREYSCALE, ColorDepth.GREYSCALE_ALPHA)

"""
@description    Checks to see if the provided color depth uses alpha values for
                transparency/blending or not.

@param[in]      color_depth - The color depth to check
@return         True if alpha is used.
"""
def has_alpha(color_depth: ColorDepth) -> bool:
    return color_depth in _RGB_DEPTHS_WITH_ALPHA or color_depth == ColorDepth.GREYSCALE_ALPHA

"""
@description    Checks to see if the provided color depth is greyscale or not

@param[in]      color_depth - The color depth
@return         True if the color depth is greyscale
"""
def is_greyscale(color_depth: ColorDepth) -> bool:
    return color_depth in (ColorDepth.GREYSCALE, ColorDepth.GREYSCALE_ALPHA)

"""
@description    Takes the bit depth and converts it to the ColorDepth enum.
                Note that this will not work on uneven color depths like RGB565.

@param[in]      num_bits - The number of bits per one color
@param[in]      alpha - True if alpha is being used
@param[in]      fill_byte - True if using an symetric color depth
@return         The ColorDepth
"""
def convert_bits_to_depth(num_bits: int, alpha: bool = False, fill_byte: bool = False) -> ColorDepth:

    color_depth = ColorDepth(convert_to_total_bits(num_bits, alpha, fill_byte))

    # Do some corrections here, since a few entries share the same integer value.
    if alpha and color_depth == ColorDepth.RGB444:
        color_depth = ColorDepth.RGBA3333
    elif alpha and color_depth == ColorDepth.RGB888:
        color_depth = ColorDepth.RGBA6666
    elif not alpha and color_depth == ColorDepth.RGBA3333:
        color_depth = ColorDepth.RGB444
    elif not alpha and color_depth == ColorDepth.RGBA6666:
        color_depth = ColorDepth.RGB888

    return color_depth

"""
@description    Takes an RGB color and rescales it from one color depth
                to a new one.

@param[in]      rgb - The RGB(A) color tuple
@param[in]      old_depth - the original color depth
@param[in]
"""
def rescale_color(rgb: tuple[int, int, int],
                  old_depth: ColorDepth,
                  new_depth: ColorDepth,
                  old_offset: bool = False,
                  new_offset: bool = False) ->  tuple[int, int, int]:

    # Let the user know there will be data loss when converting.
    if old_depth > new_depth:
        print("WARNING: Converting higher color depth to a lower one. Data loss will occur.", file=stderr, flush=True)

    # Require that the new and old depths both either have alpha or not
    if new_depth in _RGB_DEPTHS and old_depth not in _RGB_DEPTHS:
        raise ValueError("Old depth does not have alpha, while new depth does.")
    elif new_depth in _RGB_DEPTHS_WITH_ALPHA and old_depth not in _RGB_DEPTHS_WITH_ALPHA:
        raise ValueError("Old depth has alpha, while new does not.")

    # Make sure the old bit depth is the correct size for each color.
    if old_depth in _RGB_DEPTHS_WITH_ALPHA:
        old_depth = int(old_depth / 4)
    elif old_depth in _RGB_DEPTHS:
        old_depth = int(old_depth / 3)
    else:
        raise ValueError("Not a valid old color depth")
    
    # And do the same for the new depth
    if new_depth in _RGB_DEPTHS_WITH_ALPHA:
        new_depth = int(new_depth / 4)
    elif new_depth in _RGB_DEPTHS:
        new_depth = int(new_depth / 3)
    else:
        raise ValueError("Not a valid new color depth")

    new_largest_rgb_val = (2 ** (new_depth)) - (1 if new_offset else 0)
    old_largest_rgb_val = (2 ** (old_depth)) - (1 if old_offset else 0)

    new_red             = 0
    new_green           = 0
    new_blue            = 0

    new_rgb             = (new_red, new_green, new_blue)

    old_red_scalar      = 2 if old_depth is ColorDepth.RGB332 else 1
    new_red_scalar      = 2 if new_depth is ColorDepth.RGB332 else 1

    old_green_scalar    = 2 if old_depth in _FULL_BYTE_RGB_DEPTHS else 1
    new_green_scalar    = 2 if new_depth in _FULL_BYTE_RGB_DEPTHS else 1

    old_blue_scalar     = 2 if old_depth is ColorDepth.RGB233 else 1
    new_blue_scalar     = 2 if new_depth is ColorDepth.RGB233 else 1

    for index, rgb_val in enumerate(rgb):

        # Adjust scalars based on RGB index to accommodate any odd bitmodes
        if index == RGBIndex.RED:
            old_scalar = old_red_scalar
            new_scalar = new_red_scalar
        elif index == RGBIndex.GREEN:
            old_scalar = old_green_scalar
            new_scalar = new_green_scalar
        elif index == RGBIndex.BLUE:
            old_scalar = old_blue_scalar
            new_scalar = new_blue_scalar

        # Add 0.5 to round up if the new value is a decimal equal to or greater than 0.5
        new_val = ((new_largest_rgb_val * new_scalar) / (old_largest_rgb_val * old_scalar) * (rgb_val)) + 0.5

        # Correct values that end up being outside the value. Will cause some colors to be crushed.
        if new_val >= new_largest_rgb_val:
            new_val = int(new_val - (new_largest_rgb_val / old_largest_rgb_val))
        elif new_val < 0:
            new_val = 0

        new_rgb[index] = int(new_val)

    return new_rgb

"""
@description    Determines the color tint and bias of a provided RGB tuple algorithmically.

@param[in]      rgb - The RGB tuple to determine
@param[in]      color_depth - The color depth of the incoming RGB value
@param[in]      large_threshold - The maximum color difference for determining tint
@param[in]      small_threshold - The minimum color difference for determining tint
@param[in]      bias_threshold - The maximum color difference for determining bias
@return         A tuple of tint and bias
"""
def get_color_tint(rgb: list,
                   color_depth: ColorDepth  = ColorDepth.RGB888,
                   large_threshold: int     = 25,
                   small_threshold: int     = 10,
                   bias_threshold: int      = 3) -> int:
    
    # Use RGB888 to determine color balances. If the incoming color is not RGB888, rescale so it is.
    if color_depth != ColorDepth.RGB888:
        rgb = rescale_color(rgb, color_depth, ColorDepth.RGB888, False, False)

    color = Color.BLACK
    bias  = None

    red     = rgb[RGBIndex.RED]
    green   = rgb[RGBIndex.GREEN]
    blue    = rgb[RGBIndex.BLUE]

    if red == green and red == blue:

        if red == 255:
            color = Color.WHITE
        elif red > 0:
            color = Color.GREY
        # else: the color is going to be black

        # No bias in this case, since all subpixels are equal in value.

    else:
        rg_diff = red - green
        rb_diff = red - blue

        gr_diff = green - red
        gb_diff = green - blue

        br_diff = blue - red
        bg_diff = blue - green

        def determine_color(left_diff: int, right_diff: int, left_color: int, c_left_color: int, center_color: int, c_right_color: int, right_color: int) -> int:
            if right_diff >= large_threshold and left_diff >= large_threshold:
                color = center_color
            elif small_threshold <= right_diff < large_threshold and left_diff >= large_threshold:
                color = c_right_color
            elif right_diff < small_threshold and left_diff >= large_threshold:
                color = right_color
            elif right_diff >= large_threshold and small_threshold <= left_diff < large_threshold:
                color = c_left_color
            elif right_diff >= large_threshold and left_diff < small_threshold:
                color = left_color
            else:
                color = Color.GREY

            return color
        
        def determine_bias(color: int, left_diff: int, right_diff: int, left_rgb_val: int, right_rgb_val: int, grey_bias: int) -> int:
            left_color  = {red: Color.RED, green: Color.GREEN, blue: Color.BLUE}[left_rgb_val]
            right_color = {red: Color.RED, green: Color.GREEN, blue: Color.BLUE}[right_rgb_val]

            bias = None

            if color not in _NEUTRAL_COLORS:
                if left_rgb_val > right_rgb_val and left_diff >= bias_threshold:
                    bias = left_color
                elif left_rgb_val < right_rgb_val and right_diff >= bias_threshold:
                    bias = right_color

            elif color == Color.GREY:
                bias = grey_bias

            return bias
        
        if red >= green and red >= blue:
            color = determine_color(rg_diff, 
                                    rb_diff,
                                    Color.YELLOW,
                                    Color.ORANGE,
                                    Color.RED,
                                    Color.PINK,
                                    Color.MAGENTA)
            bias  = determine_bias(color,
                                   bg_diff,
                                   gb_diff,
                                   blue,
                                   green,
                                   Color.RED)

        elif green >= red and green >= blue:
            color = determine_color(gb_diff,
                                    gr_diff,
                                    Color.CYAN,
                                    Color.TEAL,
                                    Color.GREEN,
                                    Color.CHARTREUSE,
                                    Color.YELLOW)
            bias  = determine_bias(color,
                                   rb_diff,
                                   br_diff,
                                   red,
                                   blue,
                                   Color.GREEN)

        elif blue >= red and blue >= green:
            # Determine actual color and bis
            color = determine_color(br_diff,
                                    bg_diff,
                                    Color.MAGENTA,
                                    Color.PURPLE,
                                    Color.BLUE,
                                    Color.AZURE,
                                    Color.CYAN)
            bias  = determine_bias(color,
                                   gr_diff,
                                   rg_diff,
                                   green,
                                   red,
                                   Color.BLUE)

    return color, bias

"""
@description    Finds colors similar to the provided color

@param[in]      rgb - The RGB tuple to check against
@param[in]      palette - The list of RGB tuples to pull from
@param[in]      threshold - The average difference between RGB values
                needed to be considered similar.
@param[in]      exact_tint - True to filter by exact tingt, otherwise
                use similar tints
@param[in]      check_bias - True to filter by bias in addition to tint.
                If not using exact tint, this is ignored.
@return         List of similar RGB tuples
"""
def find_similar_colors(rgb: tuple[int, int, int],
                        palette: list[tuple[int, int, int]],
                        threshold: int = 256,
                        exact_tint: bool = False,
                        check_bias: bool = False,
                        color_depth: ColorDepth  = ColorDepth.RGB888,
                        large_threshold: int     = 25,
                        small_threshold: int     = 10,
                        bias_threshold: int      = 3) -> list[tuple[int, int, int]]:

    # First, determine what kind of color it is.
    color, bias = get_color_tint(rgb)

    similar_rgb = []

    if exact_tint:
        eligible_tints = (color,)
    else:
        eligible_tints = _COLOR_RELATIVES[color]

    if not exact_tint:
        check_bias = False

    # Check for colors that evaluate to have a similar tint and bias. Also check the average difference of all three
    # RGB values to determine if they are within the threshold of similarity.
    for color_tuple in palette:
        color_check, bias_check = get_color_tint(color_tuple, color_depth, large_threshold, small_threshold, bias_threshold)

        if color_check in eligible_tints and (not check_bias or bias_check == bias) and _get_avg_diff(rgb, color_tuple) <= threshold:
            similar_rgb.append(color_tuple)

    return similar_rgb

def find_closest_color(rgb: tuple[int, int, int],
                       palette: list[tuple[int, int, int]],
                       color_depth: ColorDepth  = ColorDepth.RGB888,
                       large_threshold: int     = 25,
                       small_threshold: int     = 10,
                       bias_threshold: int      = 3) -> Union[tuple[int, int, int], None]:

    closest_color           = None
    closest_r_diff          = 256
    closest_g_diff          = 256
    closest_b_diff          = 256
    closest_avg_diff        = 256

    tint, bias              = get_color_tint(rgb, color_depth, large_threshold, small_threshold, bias_threshold)

    for color in palette:
        r_diff = abs(rgb[RGBIndex.RED]    - color[RGBIndex.RED])
        g_diff = abs(rgb[RGBIndex.GREEN]  - color[RGBIndex.GREEN]) 
        b_diff = abs(rgb[RGBIndex.BLUE]   - color[RGBIndex.BLUE])

        avg_diff = (r_diff + g_diff + b_diff) / 3

        def _check_primary_diff(diff: int,
                                closest_diff: int,
                                closest_color: tuple[int, int, int],
                                closest_r_diff: int,
                                closest_g_diff: int,
                                closest_b_diff: int,
                                closest_avg_diff: int) -> None:

            if diff <= closest_diff:
                closest_color       = color
                closest_r_diff      = r_diff
                closest_g_diff      = g_diff
                closest_b_diff      = b_diff
                closest_avg_diff    = avg_diff

            return closest_color, closest_r_diff, closest_g_diff, closest_b_diff, closest_avg_diff

        def _check_complementary_diff(diff_1: int,
                                      diff_2: int,
                                      closest_diff_1: int,
                                      closest_diff_2: int,
                                      closest_color: tuple[int, int, int],
                                      closest_r_diff: int,
                                      closest_g_diff: int,
                                      closest_b_diff: int,
                                      closest_avg_diff: int) -> None:

            if diff_1 <= closest_diff_1 and diff_2 <= closest_diff_2:
                closest_color       = color
                closest_r_diff      = r_diff
                closest_g_diff      = g_diff
                closest_b_diff      = b_diff
                closest_avg_diff    = avg_diff

            return closest_color, closest_r_diff, closest_g_diff, closest_b_diff, closest_avg_diff
        
        def _check_neutral(avg_diff: int,
                           closest_color: tuple[int, int, int],
                           closest_r_diff: int,
                           closest_g_diff: int,
                           closest_b_diff: int,
                           closest_avg_diff: int) -> None:

            if avg_diff < closest_avg_diff:
                closest_color       = color
                closest_r_diff      = r_diff
                closest_g_diff      = g_diff
                closest_b_diff      = b_diff
                closest_avg_diff    = avg_diff

            return closest_color, closest_r_diff, closest_g_diff, closest_b_diff, closest_avg_diff

        calc_func = \
        {
            Color.RED:          (_check_primary_diff,       r_diff, closest_r_diff),
            Color.PINK:         (_check_complementary_diff, r_diff, b_diff, closest_r_diff, closest_b_diff),
            Color.MAGENTA:      (_check_complementary_diff, r_diff, b_diff, closest_r_diff, closest_b_diff),
            Color.PURPLE:       (_check_complementary_diff, r_diff, b_diff, closest_r_diff, closest_b_diff),
            Color.BLUE:         (_check_primary_diff,       b_diff, closest_b_diff),
            Color.AZURE:        (_check_complementary_diff, b_diff, g_diff, closest_b_diff, closest_g_diff),
            Color.CYAN:         (_check_complementary_diff, b_diff, g_diff, closest_b_diff, closest_g_diff),
            Color.TEAL:         (_check_complementary_diff, b_diff, g_diff, closest_b_diff, closest_g_diff),
            Color.GREEN:        (_check_primary_diff,       g_diff, closest_g_diff),
            Color.CHARTREUSE:   (_check_complementary_diff, g_diff, r_diff, closest_g_diff, closest_r_diff),
            Color.YELLOW:       (_check_complementary_diff, g_diff, r_diff, closest_g_diff, closest_r_diff),
            Color.ORANGE:       (_check_complementary_diff, g_diff, r_diff, closest_g_diff, closest_r_diff),
            Color.BLACK:        (_check_neutral,            avg_diff),
            Color.GREY:         (_check_neutral,            avg_diff),
            Color.WHITE:        (_check_neutral,            avg_diff)
        }[tint]

        closest_color, closest_r_diff, closest_g_diff, closest_b_diff, closest_avg_diff = calc_func[0](*calc_func[1:], closest_color, closest_r_diff, closest_g_diff, closest_b_diff, closest_avg_diff)

    return closest_color