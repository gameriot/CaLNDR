var firebase = require('firebase');
var fs = require('fs')
var config = {
    apiKey: "AIzaSyC3Ml5v1SXHo91b0flg4OuwFeaIg9SWhx4",
    authDomain: "calndr00.firebaseapp.com",
    databaseURL: "https://calndr00.firebaseio.com",
    projectId: "calndr00",
    storageBucket: "calndr00.appspot.com",
    messagingSenderId: "944701268579"
};
firebase.initializeApp(config);

var database = firebase.database();

database.ref("/activity/").once('value').then(function (data) {
    var obj = data.val();
    console.log(obj);
    fs.writeFile("Activity.txt", obj, function (err) {
        if (err) {
            return console.log(err);
        }
    }); 
});

database.ref("/duration/").once('value').then(function (data) {
    var obj = data.val();
    console.log(obj);
    fs.writeFile("Duration.txt", obj, function (err) {
        if (err) {
            return console.log(err);
        }
    });
});

database.ref("/address/").once('value').then(function (data) {
    var obj = data.val();
    console.log(obj);
    fs.writeFile("Address.txt", obj, function (err) {
        if (err) {
            return console.log(err);
        }
    });
});