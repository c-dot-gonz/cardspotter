![CardSpotter](https://raw.githubusercontent.com/relgin/cardspotter/master/Assets/CardSpotterHeader.png)
CardSpotter is a browser extension that shows automatic Magic:The Gathering card image tooltips for <video> streams. The tooltip shows a large readable card image with a scryfall link.

It works by grabbing data from HTML5 video, extracting the clicked card using OpenCV and then finding the best match from a database using image hashing.

[50s demo recorded for 2.0](https://www.youtube.com/watch?v=-vKsLunV8Kg)

If you wish to modify CardSpotter this wiki page should get you started: [How to modify CardSpotter](https://github.com/relgin/cardspotter/wiki/How-to-modify-CardSpotter)

If you wish to install Cardspotter for Chrome, you will need to load it as an unpacked extension by following these steps:
1. At the top of this page, click Code > Download ZIP
2. Extract the ZIP to a location on your computer.
3. In your Chrome address bar, go to chrome://extensions
4. In the top right, click the toggle to turn on "Developer Mode"
5. In the top left, click "Load Unpacked"
6. Navigate to where you extracted Cardspotter and select the "MagicCardSpotter" folder and click "Select Folder"

That's it! Cardspotter should show up in your extensions now! To run it, first go to a page that has a video where players are playing Magic and then go to Extensions > Cardspotter. You can also pin the Cardspotter from your extensions menu and click on the magnifying glass icon to get it to run. 
