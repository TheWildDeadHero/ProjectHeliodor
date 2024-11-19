"""
@package        PyPNGTools
@file           Platform.py

@description    This module primarily provides some platform-specific bindings and
                constants. Windows environments and POSIX-compatible environments
                differ in line endings and directory delimiters, as an example,
                and this file assigns those to flexible constants that are
                determined at runtime.

@author         William Smith
@copyright      2024
"""

"""
-----[ Imports
"""

from platform import system

"""
-----[ Constants
"""

if system() == "Windows":
    DIR_DELIMITER   = '\\'
    NEW_LINE        = '\n\r'
else:
    DIR_DELIMITER   = '/'
    NEW_LINE        = '\n'