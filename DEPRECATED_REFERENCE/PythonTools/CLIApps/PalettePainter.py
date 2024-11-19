from ImageOps import *
from API.Platform import *

if __name__ == "__main__":

    # Deal with command-line arguments
    import argparse

    parser = argparse.ArgumentParser("Palette Painter", description="Takes palette files (.pal) and paints them onto PNG images")

    parser.add_argument('--path', '-p', default=os.path.abspath(__file__).rsplit(DIR_DELIMITER, 1)[0], help="Which directory to navigate. Executing directory is used by default.", type=str)
    parser.add_argument('--recursive', '-r', default="False", help="Navigate subdirectories for palettes and image files", type=str)

    args = parser.parse_args()

    current_path = args.path
    recursive = True if args.recursive in ("T", "t", "TRUE", "true", "True") else False

    image_files = scrape_for_files(current_path, ".png", recursive)
    palette_files = scrape_for_files(current_path, ".pal", recursive)

    # Keep track of some info to print off at the end of the execution.
    num_images_found = len(image_files)
    num_palettes_found = len(palette_files)

    num_images_converted = paint_palettes_to_images(image_files, palette_files)

    print(f"Number of images found: {num_images_found}")
    print(f"Number of palettes found: {num_palettes_found}")
    print(f"Number of images written: {num_images_converted}")