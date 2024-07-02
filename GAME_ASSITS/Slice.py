import os
from PIL import Image

def slice_tilemap(input_path, output_dir):
    # Load the TileMap image
    tilemap = Image.open(input_path)

    # Define the tile size (64x64)
    tile_size = 64

    # Get the dimensions of the TileMap
    width, height = tilemap.size

    # Delete the existing "Tiles" directory (if it exists)
    if os.path.exists(output_dir):
        for filename in os.listdir(output_dir):
            file_path = os.path.join(output_dir, filename)
            os.remove(file_path)
        os.rmdir(output_dir)

    # Recreate the "Tiles" directory
    os.makedirs(output_dir)


    # Initialize the row count
    fileID    = 0
        
    # Iterate through the TileMap and slice it
    for y in range(0, height, tile_size):
        for x in range(0, width, tile_size):
            tile = tilemap.crop((x, y, x + tile_size, y + tile_size))
            # Check if the tile is not blank (e.g., all white pixels)

            if not tile.getbbox():
                fileID += 1
                continue  # Skip blank tiles
            
            # Save the tile with a filename like "0000.png", "0001.png", ...
            tile_filename = f"{output_dir}/{fileID:04d}.png"
            tile.save(tile_filename)
            fileID += 1  
                  
                
               

if __name__ == "__main__":
    input_tilemap_path = "TileMap.png"  # Specify the path to your TileMap image
    output_directory = "Tiles"  # Specify the output directory

    slice_tilemap(input_tilemap_path, output_directory)
    print("TileMap sliced successfully!")
