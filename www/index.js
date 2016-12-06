var page = new tabris.Page({
  topLevel: true,
  title: "myapp"
  // onNavigateTo: function(){
  //   // capture callback
  //   var captureSuccess = function(mediaFiles) {
  //     var i, path, len;
  //     for (i = 0, len = mediaFiles.length; i < len; i += 1) {
  //       path = mediaFiles[i].fullPath;
  //       // do something interesting with the file
  //     }
  //   };
  //
  //   // capture error callback
  //   var captureError = function(error) {
  //    alert('Error code: ' + error.code, null, 'Capture Error');
  //   };
  //
  //   // start audio capture
  //   window.capture.captureAudio(captureSuccess, captureError, {limit:2});
  // }
});
new tabris.TextView({
  layoutData: {centerX: 0, centerY: 0},
  text: "My First App"
}).appendTo(page);

new tabris.Composite({
  layoutData: {left: 15, right: 15, top: 'prev() 10', height: 40},
  background: 'blue'
}).on('tap', function(widget, event){
  // var captureSuccess = function(mediaFiles) {
  //   widget.set('background', 'green');
  //   var i, path, len;
  //   for (i = 0, len = mediaFiles.length; i < len; i += 1) {
  //     path = mediaFiles[i].fullPath;
  //     // do something interesting with the file
  //   }
  // };
  // //
  // // // capture error callback
  // var captureError = function(error) {
  //   widget.set('background', 'red');
  //   //alert('Error code: ' + error.code, null, 'Capture Error');
  // };
  // //
  // // // start audio capture
  // navigator.device.capture.captureAudio(captureSuccess, captureError, {limit:2});

  startRecording();
}).appendTo(page);

new tabris.Composite({
  layoutData: {left: 15, right: 15, top: 'prev() 10', height: 40},
  background: 'red'
}).on('tap', function(widget, event){
  // var captureSuccess = function(mediaFiles) {
  //   widget.set('background', 'green');
  //   var i, path, len;
  //   for (i = 0, len = mediaFiles.length; i < len; i += 1) {
  //     path = mediaFiles[i].fullPath;
  //     // do something interesting with the file
  //   }
  // };
  // //
  // // // capture error callback
  // var captureError = function(error) {
  //   widget.set('background', 'red');
  //   //alert('Error code: ' + error.code, null, 'Capture Error');
  // };
  // //
  // // // start audio capture
  // navigator.device.capture.captureAudio(captureSuccess, captureError, {limit:2});

  stopRecording();
}).appendTo(page);

new tabris.Composite({
  layoutData: {left: 15, right: 15, top: 'prev() 10', height: 40},
  background: 'yellow'
}).on('tap', function(widget, event){
  // var captureSuccess = function(mediaFiles) {
  //   widget.set('background', 'green');
  //   var i, path, len;
  //   for (i = 0, len = mediaFiles.length; i < len; i += 1) {
  //     path = mediaFiles[i].fullPath;
  //     // do something interesting with the file
  //   }
  // };
  // //
  // // // capture error callback
  // var captureError = function(error) {
  //   widget.set('background', 'red');
  //   //alert('Error code: ' + error.code, null, 'Capture Error');
  // };
  // //
  // // // start audio capture
  // navigator.device.capture.captureAudio(captureSuccess, captureError, {limit:2});

  playMusic();
}).appendTo(page);

var ua = navigator.userAgent.toLowerCase();

var phoneCheck = {
  ios: ua.match(/(iphone|ipod|ipad)/i),
  blackberry: ua.match(/blackberry/i),
  android: ua.match(/android/i),
  windowsphone: ua.match(/windows phone/i)
};

// detect browser
var browserCheck = {
//   chrome: ua.match(/chrome/i),
//   ie: ua.match(/msie/i),
//   firefox: ua.match(/firefox/i),
//   safari: ua.match(/safari/i), //this one is the same as chrome.
//   opera: ua.match(/opera/i)
};

// detect HTML5 tag support
var myDeviceSupport = {
  // HTML5_audio: !!(document.createElement('audio').canPlayType),
  // HTML5_audio_mp3: !!(document.createElement('audio').canPlayType) && document.createElement('audio').canPlayType('audio/mpeg') !== "",
  // HTML5_audio_wav: !!(document.createElement('audio').canPlayType) && document.createElement('audio').canPlayType('audio/wav') !== "",
  // HTML5_geolocation: navigator.geolocation
};

/*jslint browser:true, devel:true, white:true, vars:true, eqeq:true, -W069, -W020*/
/*global $:true, phoneCheck:false, Media:false, LocalFileSystem:false*/
/*
 * Copyright (c) 2014, Intel Corporation. All rights reserved.
 * File revision: 04 February 2014
 * Please see http://software.intel.com/html5/license/samples
 * and the included README.md file for license terms and conditions.
 */

var my_recorder = null, my_player = null;
var progressTimmer = null;
var createdStatus = false;
var recTime = 0;

// for recording: do not specify any directory
var mediaFileFullName = null;
var mediaRecFile = "myRecording100.wav";
var checkFileOnly = false;
var mediaFileExist = false;
var myMediaState = {start: 1,
  recording: 2,
  finishRec: 3,
  playback: 4,
  paused: 5,
  stopped: 6 };

/* console.log et al are not always available in Firefox. This silences it and prevents a JS error. */
if(typeof console === "undefined") {
  console = { log: function() { } };
}



function onOK_GetFile(fileEntry) {
  console.log("***test: File " + mediaRecFile + " at " + fileEntry.fullPath);

  // save the full file name
  mediaFileFullName = fileEntry.fullPath;
  if (phoneCheck.ios)
    mediaRecFile = mediaFileFullName;

  if (checkFileOnly === true) { // check if file exist at app launch.
    mediaFileExist = true;

    //setButtonState(myMediaState.finishRec);
  }
  else { // record on iOS

    // create media object using full media file name
    my_recorder = new Media(mediaRecFile, onMediaCallSuccess, onMediaCallError);

    // specific for iOS device: recording start here in call-back function
    recordNow();
  }
}

function onSuccessFileSystem(fileSystem) {
  console.log("***test: fileSystem.root.name: " + fileSystem.root.name);

  if (checkFileOnly === true)
    fileSystem.root.getFile(mediaRecFile, { create: false, exclusive: false }, onOK_GetFile, null);
  else
    fileSystem.root.getFile(mediaRecFile, { create: true, exclusive: false }, onOK_GetFile, null);

}

function checkMediaRecFileExist() {
  checkFileOnly = true;
  window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, onSuccessFileSystem, null);
}

/*Enable Mic image: Display Record or active image*/
function enableMic(status){
  if (status === 0){
    //document.getElementById('startRecID').src = "./images/simplemicrophone_rec.png";
    //document.getElementById('startRecID').className = " ";
  }
  else if (status == 1){
    //document.getElementById('startRecID').src = "./images/simplemicrophone.png";
    //document.getElementById('startRecID').className += " greenoutline";
  }
}


function recordNow() {
  if (my_recorder) {
    my_recorder.startRecord();
    //document.getElementById('RecStatusID').innerHTML = "Status: recording";
    console.log("***test:  recording started: in startRecording()***");
  }
  else
    console.log("***test:  my_recorder==null: in startRecording()***");

  // reset the recTime every time when recording
  recTime = 0;

  // Stop recording after 10 sec
  progressTimmer = setInterval(function() {
    recTime = recTime + 1;
    setAudioPosition('media_rec_pos', recTime + " sec");
    if (recTime >= 10)
      stopRecording();
    console.log("***test: interval-func()***");
  }, 1000);
}

// Record audio
//
function startRecording() {

  enableMic(1);
  // document.getElementById('stopRecID').removeAttribute("style");
  // // change buttons state
  // setButtonState(myMediaState.recording);

  // create media object - overwrite existing recording
  if (my_recorder)
    my_recorder.release();

  //if (phoneCheck.android) {
    my_recorder = new Media(mediaRecFile, onMediaCallSuccess, onMediaCallError);
    console.log("***test: new Media() for android ***");

    recordNow();
  // }
  // else if (phoneCheck.windowsphone) {
  //   my_recorder = new Media(mediaRecFile, onMediaCallSuccess, onMediaCallError);
  //   console.log("***test: new Media() for Windows Phone ***");
  //
  //   recordNow();
  // }
  // else if (phoneCheck.ios) {
  //   //first create the file
  //   checkFileOnly = false;
  //   window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, onSuccessFileSystem, function() {
  //     console.log("***test: failed in creating media file in requestFileSystem");
  //   });
  //
  //   console.log("***test: new Media() for ios***");
  // }

}

// Stop recording
function stopRecording() {
  enableMic(0);
  //document.getElementById('stopRecID').style.display="none";
  // enable "record" button but disable "stop"
  //setButtonState(myMediaState.finishRec);

  if (my_recorder)
    my_recorder.stopRecord(); // the file should be moved to "/sdcard/"+mediaRecFile

  clearProgressTimmer();

  //document.getElementById('RecStatusID').innerHTML = "Status: stopped record";
  console.log("***test: recording stopped***");
}

// Play audio
//
function playMusic() {
  if (my_player === null) { // play existing media recorded from previous session

    // the existing medail should be on /sdcard/ for android.
    // if (phoneCheck.android) {
    //   my_player = new Media("/sdcard/" + mediaRecFile, onMediaCallSuccess, onMediaCallError);
    //
    //   console.log("***test:  Open file:" + mediaRecFile);
    // } else if (phoneCheck.windowsphone) // windows phone
    //   my_player = new Media(mediaRecFile, onMediaCallSuccess, onMediaCallError);
    // else if (phoneCheck.ios) {
    //   console.log('ios works');
      my_player = new Media(mediaFileFullName, onMediaCallSuccess, onMediaCallError);
  }

  // Play audio
  if (my_player) {
    my_player.play();
    //document.getElementById('PlayStatusID').innerHTML = "<p></p>Status: playing...";

    //setButtonState(myMediaState.playback);

    // Update media position every second
    clearProgressTimmer();
    progressTimmer = setInterval(function () {
      // get my_player position
      my_player.getCurrentPosition(
          // success callback
          function (position) {
            if (position >= 0)
              setAudioPosition('media_pos', (position) + " sec");
            else {
              // reached end of media: same as clicked stop-music
              clearProgressTimmer();
              setAudioPosition('media_pos', "0 sec");
              //document.getElementById('PlayStatusID').innerHTML = "Status: stopped";
              //setButtonState(myMediaState.stopped);
            }
          },
          // error callback
          function (e) {
            //document.getElementById('PlayStatusID').innerHTML = "Status: Error on getting position - " + e;
            setAudioPosition("Error: " + e);
          });
    }, 1000);
  }
}
// Pause audio
//
function pauseMusic() {
  if (my_player) {
    my_player.pause();
    //document.getElementById('PlayStatusID').innerHTML = "<p>Status: paused</p>";

    clearProgressTimmer();
    //setButtonState(myMediaState.paused);
  }
}
// Stop audio
//
function stopMusic() {
  if (my_player) {
    setAudioPosition('media_pos', "0 sec");
    //setButtonState(myMediaState.stopped);

    my_player.stop();

    // should not be necessary, but it is needed in order to play again.
    my_player.release();
    my_player = null;

    clearProgressTimmer();
    //document.getElementById('PlayStatusID').innerHTML = "<p>Status: stopped</p>";
  }
}

function clearProgressTimmer() {
  if (progressTimmer) {
    clearInterval(progressTimmer);
    progressTimmer = null;
  }
}
// Media() success callback
function onMediaCallSuccess() {
  createdStatus = true;
  console.log("***test: new Media() succeeded ***");
}
// Media() error callback
function onMediaCallError(error) {
  console.log("***test: new Media() failed ***");
}
// Set audio position
//
function setAudioPosition(audioPosID, position) {
  if(audioPosID == "media_rec_pos"){
    //document.getElementById(audioPosID).innerHTML = "Recording position: 00:00:"+position;
  }
  if(audioPosID == "media_pos"){
    //document.getElementById(audioPosID).innerHTML = "Playback position: 00:00:"+position;
  }
}


// var my_audio;
//
//
//
// function playMusic() {
//   if (my_audio === null) { // play existing media recorded from previous session
//
//       my_audio = new Media(mediaFileFullName, onMediaCallSuccess, onMediaCallError);
//
//   }
//
// }
//
// function recordNow() {
//   if (my_audio) {
//     my_audio.startRecord();
//     //document.getElementById('RecStatusID').innerHTML = "Status: recording";
//     console.log("***test:  recording started: in startRecording()***");
//   }
// }
//
//
// function onOK_GetFile(fileEntry) {
//     // create media object using full media file name
//     my_audio = new Media(mediaRecFile, onMediaCallSuccess, onMediaCallError);
//
//     // specific for iOS device: recording start here in call-back function
//     recordNow();
// }
//
// function onSuccessFileSystem(fileSystem) {
//   console.log("***test: fileSystem.root.name: " + fileSystem.root.name);
//   fileSystem.root.getFile(mediaRecFile, { create: true, exclusive: false }, onOK_GetFile, null);
//
// }
//
// function startRecording() {
//
//     //first create the file
//     //checkFileOnly = false;
//     window.requestFileSystem(LocalFileSystem.PERSISTENT, 0, onSuccessFileSystem, function() {
//       console.log("***test: failed in creating media file in requestFileSystem");
//     });
//     console.log("***test: new Media() for ios***");
// }


page.open();