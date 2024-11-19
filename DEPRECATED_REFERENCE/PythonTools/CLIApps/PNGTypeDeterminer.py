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

    print(("-" * 80) + "\nFiles | PNG type\n" + ("-" * 80))

    for file in files:

        file = str(file)

        file_data = png.Reader(filename=file)
        file_data.read()

        apply_background = False

        directory, filename = file.rsplit(DIR_DELIMITER, 1)

        filename, file_ext = filename.rsplit('.', 1)

        print(f"{filename}: {file_data.color_type}")

        if file_data.color_type == 6:
            colors = list()
            bitmap = list()

            width, height, row_data, info = file_data.asRGBA8()

            for row in row_data:

                current_row = list()

                for index in range(width):

                    if apply_background:
                        a = row[index + 3] / 255

                        # Just assume the background is white for now. Code will be implemented later.
                        r = int((row[index]     * a) + (255 * (1 - (a))) + 0.5)
                        g = int((row[index + 1] * a) + (255 * (1 - (a))) + 0.5)
                        b = int((row[index + 2] * a) + (255 * (1 - (a))) + 0.5)
                    else:
                        r = int(row[index])
                        g = int(row[index + 1])
                        b = int(row[index + 2])

                        # Put on a white background. May result in some data loss, but that can be fixed manually.
                        if r == 0 and g == 0 and b == 0:
                            r = 255
                            g = 255
                            b = 255

                    rgb = (r, g, b)

                    if (r, g, b) not in colors:
                        colors.append(rgb)

                    current_row.append(colors.index(rgb))

                bitmap.append(current_row)

            write_image(os.path.join(directory, filename + "_INDEXED." + file_ext), width, height, bitmap, colors)
            print("Image indexed.")
                    

            #for row in row_data:
#
            #    rgb_val = list()
#
            #    for color in row:
#
            #        if argb_val[0:2] not in colors:
            #            colors.append(argb_val[0:2])
#
            #    current_row.append(colors.index(argb_val[0:2]))
#
            #    if len(current_row) == file_data.width:
            #        bitmap.append(current_row)
            #        current_row.clear()
#
#
            #


