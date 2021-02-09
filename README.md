<img src="https://github.com/Gusseth/Kokoro-Slideshows/blob/master/images/banner.png?raw=true">
<br>

# Kokoro Slideshows - A Noh Performance of Tiles.

## An Overview
*Kokoro Slideshow* is a small program that uses [nearest neighbour search](https://en.wikipedia.org/wiki/Nearest_neighbor_search) to approximate pixels into tiles.
This is done through the usage of [k-d trees](https://en.wikipedia.org/wiki/K-d_tree) and [quickselect](https://en.wikipedia.org/wiki/Quickselect) algorithm to perform a search.
Performance is a goal for this project, so this will also be the pilot program of the soon-to-be public Shameimaru Project.

## Examples 
- [Bad Apple](https://www.youtube.com/watch?v=dgY6d-0OFho) (This uses an older version of the algorithm.)

## User Stories
The following list would be the main goals for Kokoro Slideshow:
- As a user, I should be able to load an image and generate a mosaic that maps every pixel into a tile of various size
- As a user, I should be able to load an image and generate a mosaic that subdivides the image into tiles instead of expanding it.
- As a user, I should be able to import a video with sound and expect an exported, mosaic'd video with sound.
- As a user, I should be able to run this program efficiently.

## Project Citations
- This project was originally a Programming Assignment from UBC CPSC 221. I have rewritten the libraries provided by the intructors for more performance.
- This project uses the [lodePNG](https://lodev.org/lodepng/) library provided by Lode Vandevenne.