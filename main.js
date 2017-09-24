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
    fs.appendFile('file.txt', obj, function (err) {
        if (err) {
            console.log('there was an error: ', err);
            return;
        }
    });
});
database.ref("/duration/").once('value').then(function (data) {
    var obj = data.val();
    console.log(obj);
    fs.appendFile('file.txt', obj, function (err) {
        if (err) {
            console.log('there was an error: ', err);
            return;
        }
    });
});
database.ref("/address/").once('value').then(function (data) {
    var obj = data.val();
    console.log(obj);
    fs.appendFile('file.txt', obj, function (err) {
        if (err) {
            console.log('there was an error: ', err);
            return;
        }
    });
});



