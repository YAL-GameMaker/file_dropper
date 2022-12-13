{
  "optionsFile": "options.json",
  "options": [],
  "exportToGame": true,
  "supportedTargets": 113497714299118,
  "extensionVersion": "1.0.0",
  "packageId": "",
  "productId": "",
  "author": "",
  "date": "2019-12-12T01:34:29",
  "license": "Proprietary",
  "description": "",
  "helpfile": "",
  "iosProps": true,
  "tvosProps": false,
  "androidProps": true,
  "installdir": "",
  "files": [
    {"filename":"file_dropper.dll","origname":"extensions\\file_dropper.dll","init":"","final":"","kind":1,"uncompress":false,"functions":[
        {"externalName":"file_dropper_init_raw","kind":11,"help":"","hidden":true,"returnType":2,"argCount":2,"args":[
            1,
            2,
          ],"resourceVersion":"1.0","name":"file_dropper_init_raw","tags":[],"resourceType":"GMExtensionFunction",},
        {"externalName":"RegisterCallbacks","kind":11,"help":"","hidden":true,"returnType":2,"argCount":4,"args":[
            1,
            1,
            1,
            1,
          ],"resourceVersion":"1.0","name":"RegisterCallbacks","tags":[],"resourceType":"GMExtensionFunction",},
      ],"constants":[
        
      ],"ProxyFiles":[
        {"name":"file_dropper_x64.dll","tags":[],"resourceVersion":"1.0","resourceType":"GMProxyFile","TargetMask":6,},
      ],"copyToTargets":9223372036854775807,"order":[
        {"name":"file_dropper_init_raw","path":"extensions/file_dropper/file_dropper.yy",},
        {"name":"RegisterCallbacks","path":"extensions/file_dropper/file_dropper.yy",},
      ],"resourceVersion":"1.0","name":"","tags":[],"resourceType":"GMExtensionFile",},
    {"filename":"file_dropper.gml","origname":"extensions\\gml.gml","init":"","final":"","kind":2,"uncompress":false,"functions":[
        {"externalName":"file_dropper_prepare_buffer","kind":11,"help":"","hidden":true,"returnType":2,"argCount":1,"args":[
            2,
          ],"resourceVersion":"1.0","name":"file_dropper_prepare_buffer","tags":[],"resourceType":"GMExtensionFunction",},
      ],"constants":[
        
      ],"ProxyFiles":[],"copyToTargets":9223372036854775807,"order":[
        {"name":"file_dropper_prepare_buffer","path":"extensions/file_dropper/file_dropper.yy",},
      ],"resourceVersion":"1.0","name":"","tags":[],"resourceType":"GMExtensionFile",},
    {"filename":"autogen.gml","origname":"extensions\\autogen.gml","init":"","final":"","kind":2,"uncompress":false,"functions":[
        {"externalName":"file_dropper_init","kind":2,"help":"file_dropper_init()->bool","hidden":false,"returnType":2,"argCount":0,"args":[],"resourceVersion":"1.0","name":"file_dropper_init","tags":[],"resourceType":"GMExtensionFunction",},
      ],"constants":[
        
      ],"ProxyFiles":[],"copyToTargets":-1,"order":[
        {"name":"file_dropper_init","path":"extensions/file_dropper/file_dropper.yy",},
      ],"resourceVersion":"1.0","name":"","tags":[],"resourceType":"GMExtensionFile",},
  ],
  "classname": "",
  "tvosclassname": "",
  "tvosdelegatename": "",
  "iosdelegatename": "",
  "androidclassname": "",
  "sourcedir": "",
  "androidsourcedir": "",
  "macsourcedir": "",
  "maccompilerflags": "",
  "tvosmaccompilerflags": "",
  "maclinkerflags": "",
  "tvosmaclinkerflags": "",
  "androidcodeinjection": "",
  "ioscodeinjection": "",
  "tvoscodeinjection": "",
  "iosSystemFrameworkEntries": [],
  "tvosSystemFrameworkEntries": [],
  "iosThirdPartyFrameworkEntries": [],
  "tvosThirdPartyFrameworkEntries": [],
  "IncludedResources": [],
  "androidPermissions": [],
  "copyToTargets": 113497714299118,
  "parent": {
    "name": "Extensions",
    "path": "folders/Extensions.yy",
  },
  "resourceVersion": "1.2",
  "name": "file_dropper",
  "tags": [],
  "resourceType": "GMExtension",
}