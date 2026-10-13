#!/bin/bash
# makePhotos.bash -- build a fresh test inbox for CS-265 Project 1
#
# Usage:  bash makePhotos.bash
#
# Creates ./inbox full of empty placeholder "photos" and removes ./sorted,
# so you can run photosort against a known starting point as often as you like.
# Only ./inbox and ./sorted in the current directory are touched.

inbox=inbox

if [[ -e sorted || -e $inbox ]] ; then
    echo "Removing old ./$inbox and ./sorted"
fi
rm -rf -- "$inbox" sorted
mkdir -- "$inbox" || exit 1

files=(
    # Android camera
    'IMG_20260914_153012.jpg'
    'IMG_20260914_153012(1).jpg'
    'IMG_20260914_153012 (1).jpg'
    'IMG_20260915_081500.JPG'
    'IMG_20261002_190245.jpeg'
    'IMG_20260921_120000.mp4'
    'IMG_20260830_231559.jpg'

    # Google Pixel
    'PXL_20260920_101530123.jpg'
    'PXL_20260920_101530987.jpg'
    'PXL_20261005_174502001.mp4'
    'PXL_20260912_090000000.PNG'

    # Screenshots
    'Screenshot_2026-09-14-15-30-12.png'
    'Screenshot_2026-10-01-08-05-09.png'
    'Screenshot_2026-10-01-08-05-09 (1).png'
    'Screenshot_2026-09-28-22-14-37.PNG'

    # WhatsApp
    'IMG-20260914-WA0007.jpg'
    'IMG-20260914-WA0008.jpg'
    'IMG-20261003-WA0001.jpeg'
    'IMG-20260919-WA0012.mp4'

    # Right shape, impossible date or time
    'IMG_20261399_153012.jpg'
    'IMG_20260914_246000.jpg'
    'PXL_20260932_101530123.jpg'

    # No date in the name, or not quite the right shape
    'IMG_1234.HEIC'
    'IMG_1235.HEIC'
    'IMG_1234(1).HEIC'
    'DSC01234.JPG'
    'DSC01235.JPG'
    'vacation pic.jpeg'
    'beach day 2.jpg'
    'IMG_2026091_153012.jpg'
    'img_20260914_153012.jpg'
    'IMG_20260914_153012_edit.jpg'
    'IMG-20260914-WA07.jpg'
    'Screenshot_2026-9-14-15-30-12.png'

    # Not photos -- these get skipped
    'IMG_1234.AAE'
    'IMG_1235.AAE'
    'notes.txt'
    'README'
    'IMG_20260914_153012.gif'
)

for f in "${files[@]}" ; do
    touch -- "$inbox/$f"
done

# Things photosort should ignore silently
touch -- "$inbox/.DS_Store"
mkdir -- "$inbox/Camera Roll Backup"
touch -- "$inbox/Camera Roll Backup/IMG_20260101_120000.jpg"

echo "Created ./$inbox with ${#files[@]} files (plus a hidden file and a subdirectory)."
