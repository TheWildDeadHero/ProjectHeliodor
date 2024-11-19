from ImageOps import *
import functools

# Load a palette from a defined palette file. The format must follow the same palette file structure as the one used in the pret disassemblies.
def load_palette_from_file(filename: str) -> list:
    palette = None

    with open(filename, "r") as file:
        palette = file.readlines()

        # Just delete the format info since we already know it.
        del palette[0:3]

        for index, color in enumerate(palette):
            color.strip("\n")
            palette[index] = color.split(" ")

            for sub_index, val in enumerate(palette[index]):
                palette[index][sub_index] = int(val, base=10)

            palette[index] = tuple(palette[index])
    
    return palette


"""
@group          Argument
"""

overload

"""
@enum           _ArgumentKeys
@description    Internal enum used for API 
"""
class _ArgumentKeys(StrEnum):
    FILE            = 'file'
    FILENAME        = 'filename'
    PNG             = 'png'
    KEYWORDS        = '__provided_arguments_hidden__'

def flexible_overload(*args_keywords: str,
                      valid_args_combos: list = [],
                      positional_args: bool = False,
                      min_expected: int = 1,
                      max_expected: int = 1,
                      unknown_keywords: bool = False) -> Union[function, object]:

    if len(args_keywords) == 0:
        raise KeyError("At least one keyword required. None provided")
    
    def check_validity(func: function) -> function:
        functools.wraps(func)

        class ArgumentError(Exception):
            pass

        def check_arguments(*args, **kwargs):
            if min_expected == max_expected and len(kwargs) != min_expected:
                raise ArgumentError(f"Expected exactly {min_expected} keyword argument{'s' if min != 1 else ''}. {len(kwargs)} provided.")
            elif len(kwargs) > max_expected:
                raise ArgumentError(f"Expected at most {max_expected} keyword argument{'s' if min != 0 else ''}. {len(kwargs)} provided.")
            elif len(kwargs) < min_expected:
                raise ArgumentError(f"Expected at least {min_expected} keyword argument{'s' if min != 0 else ''}. {len(kwargs)} provided.")
            
            if len(valid_args_combos) > 0 and kwargs.keys() not in valid_args_combos:
                raise ArgumentError("Not a valid argument combination.")
            
            if len(args) > 0 and not positional_args:
                raise ArgumentError("Positional arguments provided, but not accepted.")
            
            provided_keywords = kwargs.keys()

            if _ArgumentKeys.KEYWORDS in provided_keywords:
                raise ArgumentError(f"Protected keyword \"{_ArgumentKeys.KEYWORDS}\" cannot be used.")
            else:
                kwargs[_ArgumentKeys.KEYWORDS] = []

            for keyword in provided_keywords:
                if keyword not in args_keywords and not unknown_keywords:
                    raise ArgumentError(f"Keyword \"{keyword}\" not an accepted keyword argument.")
                kwargs[_ArgumentKeys.KEYWORDS].append(keyword)

            if len(kwargs) == 2:
                kwargs[_ArgumentKeys.KEYWORDS] = kwargs[_ArgumentKeys.KEYWORDS][0]
            
            return func(*args, **kwargs)
        
        return check_arguments

    return check_validity