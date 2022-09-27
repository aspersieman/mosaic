# Mosaic Maker
Tool to generate a mosaic from constituent images

## Concept 

Tool that should take a master image and a series of source images. The source images should be converted into a series of thumbnails and it should calculate the average colours for each thumbnail. The master image should then be broken into segments equal to the size of a thumbnail image. A new image should be created that is constructed from the thumbnail images which should match the master image by getting the closest average colour for each of the master image's segments from the thumbnail library.

## Goals 

Should be able to run this tool on a normal computer or in the browser (wasm).

## Tasks 

 1. Thumbnail class that:
   a. Iterates over a series of images and converts them into a thumbnail size
   b. Calculates the average colour of each thumbnail
 2. Image class that:
   a. Calculates the average colour of a given image
 3. Mosaic class that:
   a. Accepts a master image, list of thumbnails, rows, cols
   b. Creates a new image matching the master in size
   c. Iterates over each segment for each row and col and finds a matching thumbnail (based on closest average colour)
   d. Stitches a mosaic together from the thumbnails
   e. Returns 'stitched' together image data
 4. Command line application:
   a. Gets image data from master, thumbnails on disk and passes it to 1, 2, 3
   b. Saves the resultant mosaic to disk
 5. Wasm library:
   a. Accepts image data from browser and passes it to 1, 2, 3
   b. Returns the resultant mosaic in base64

## Structure 

 - build: -> temporary destination of build code
 - docker: -> docker build environment for easier distribution
 - src: -> all source code
    - |_ common: -> shared classes
    - |_ standard: -> code for computer version
    - |_ wasm: -> code for wasm version
 - Makefile
 - docker-compose.yml
