from ImageOps import *
from API.Platform import *

if __name__ == "__main__":

    # Deal with command-line arguments
    import argparse

    parser = argparse.ArgumentParser("Palette Fixer", description="Takes RGB555 images in an RGB888 format and corrects the palettes.")

    parser.add_argument('--path', '-p', default=os.path.abspath(__file__).rsplit(DIR_DELIMITER, 1)[0], help="Which directory to navigate. Executing directory is used by default.", type=str)
    parser.add_argument('--recursive', '-r', default="False", help="Navigate subdirectories for palettes and image files", type=str)

    args = parser.parse_args()

    current_path = args.path
    recursive = True if args.recursive in ("T", "t", "TRUE", "true", "True") else False

    files = scrape_for_files(current_path, ".png", recursive)

    number_palettes_fixed = fix_palette(files=files)

    print(f"Number of palettes fixed: {number_palettes_fixed}")