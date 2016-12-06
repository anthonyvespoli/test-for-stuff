/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

var cordovaBridge = (function() {
  /*globals cordova: false */

  var pluginProxies = {};

  var massageMessageNativeToJs = function(message) {
    if (message.CDVType == 'ArrayBuffer') {
      var stringToArrayBuffer = function(str) {
        var ret = new Uint8Array(str.length);
        for (var i = 0; i < str.length; i++) {
          ret[i] = str.charCodeAt(i);
        }
        return ret.buffer;
      };
      var base64ToArrayBuffer = function(b64) {
        return stringToArrayBuffer(atob(b64));
      };
      message = base64ToArrayBuffer(message.data);
    }
    return message;
  };

  var createIOSMessage = function(message) {
    var args = [];
    if (!message || !message.hasOwnProperty('CDVType')) {
      args.push(message);
    } else if (message.CDVType == 'MultiPart') {
      message.messages.forEach(function(e) {
        args.push(massageMessageNativeToJs(e));
      });
    } else {
      args.push(massageMessageNativeToJs(message));
    }
    return args;
  };

  var processIOSEvent = function(event) {
    var callbackId = event.callbackId;
    var status = event.status;
    var keepCallback = event.keepCallback;
    var success = status === 0 || status === 1;
    var message = createIOSMessage(event.message);
    cordova.callbackFromNative(callbackId, success, status, message, keepCallback);
  };

  var getPlugin = function(service) {
    var plugin = pluginProxies[ service ];
    if (typeof plugin === "undefined") {
      plugin = tabris.create("cordova.plugin", {service: service});
      plugin.on("finish", function(event) {
        processIOSEvent(event);
      });
      pluginProxies[ service ] = plugin;
    }
    return plugin;
  };

  return {
    exec: function(service, action, args, callbackId ) {
      var plugin = getPlugin(service);
      plugin._nativeCall("exec", {action: action, arguments: args, callbackId: callbackId});
    }
  };

}());

function tabrisExec() {
  var successCallback, failCallback, service, action, actionArgs, splitCommand;
  var callbackId = null;
  if (typeof arguments[0] !== "string") {
    // FORMAT ONE
    successCallback = arguments[0];
    failCallback = arguments[1];
    service = arguments[2];
    action = arguments[3];
    actionArgs = arguments[4];
    // Since we need to maintain backwards compatibility, we have to pass
    // an invalid callbackId even if no callback was provided since plugins
    // will be expecting it. The Cordova.exec() implementation allocates
    // an invalid callbackId and passes it even if no callbacks were given.
    callbackId = "INVALID";
  } else {
    // FORMAT TWO, REMOVED
    try {
      splitCommand = arguments[0].split(".");
      action = splitCommand.pop();
      service = splitCommand.join(".");
      actionArgs = Array.prototype.splice.call(arguments, 1);
      console.log(
        "The old format of this exec call has been removed (deprecated since 2.1). Change to: " +
        "cordova.exec(null, null, \"" + service + "\", \"" + action + "\"," + JSON.stringify(actionArgs) + ");"
      );
      return;
    } catch (e) {
    }
  }
  // If actionArgs is not provided, default to an empty array
  actionArgs = actionArgs || [];
  // Register the callbacks and add the callbackId to the positional
  // arguments if given.
  if (successCallback || failCallback) {
    callbackId = service + cordova.callbackId++;
    cordova.callbacks[callbackId] = {success: successCallback, fail: failCallback};
  }
  cordovaBridge.exec(service, action, actionArgs, callbackId);
}

module.exports = tabrisExec;
