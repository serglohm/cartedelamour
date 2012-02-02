var URLSTART = 'http://www.mobileadv.ru';
var SID = 0;

var imageModels = new Object();

function func() {

}


function login(){
    var VERSION = 1;
    var IMEI = '0123456789012345';
    var uname = 'user1';
    var password = '1';
    var url = URLSTART + '/cgi-bin/widget.cgi?imei=' + IMEI + '&uname=' + uname + '&pass=' + password + '&cmd=login&version=' + VERSION + '&rnd=' + Math.random(1);

    Code.getJSON(url, loginCallback);
}

function onImageLoaded(iid){
    console.log("ImageLoaded: " + iid);
    console.log("imageModels ");
    console.log(Code.obj2json(imageModels["iid" + iid]));
    var el = imageModels["iid" + iid];
    for(var i in el){
        mainPage.userMessagesModel.setProperty(el[i], "imgLoaded", 1)
    }
}

function onImageUploaded(iid){
    console.log("onImageUploaded " + iid);
    mainPage.debugText = "image Uploaded: " + iid;
}

function loginCallback(data){
    //console.log(Code.obj2json(data));
    SID = data.sid;
    qtengine.setSID(SID);

    qtengine.imageLoaded.connect(onImageLoaded);
    qtengine.imageUploaded.connect(onImageUploaded);
    for(var i = 0; i < data.users.user_users.length; i++){
        var user = data.users.user_users[i];
        //console.log(Code.obj2json(user));
        mainPage.usersModel.append(user);
    }
}

function engineViewUserMessages(puid, page){
    var url = URLSTART + "/cgi-bin/widget.cgi?cmd=view_user_messages&param1=" + puid + "&param2=" + page + "&sid=" + SID + "&rnd=" + Math.random(1);
    Code.getJSON(url, viewUserMessagesCallback);
}


function viewUserMessagesCallback(data){
    var tempModels = new Object();
    for(var i = 0; i < data.messages.length; i++){
        var message = data.messages[i];
        console.log(Code.obj2json(message));
        message.imgLoaded = qtengine.hasImage(message.iid);
        mainPage.userMessagesModel.append(message);
        var obj = tempModels["iid" + message.iid]? tempModels["iid" + message.iid]: new Object();
        obj["i" + i] = i;
        tempModels["iid" + message.iid] = obj;
    }
    imageModels = tempModels;

}
