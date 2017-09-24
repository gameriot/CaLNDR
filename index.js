/*
* HTTP Cloud Function.
*
* @param {Object} req Cloud Function request context.
* @param {Object} res Cloud Function response context.
*/

var firebase = require('firebase');

var activityFinal = "";
var durationFinal = 0; 
var addressFinal = ""; 

exports.CaLNDR = function CaLNDR (req, res) {

  	let activity = req.body.result.parameters['activity']
  	let duration = req.body.result.parameters['duration']
  	let address = req.body.result.parameters['address']

  	if (address != "") {
  		addressFinal = address
  		updateData()
  		response3 = "Ok, I am computing an optimized schedule. Please wait..." 
	  	res.setHeader('Content-Type', 'application/json'); //Requires application/json MIME type
	  	res.send(JSON.stringify({ "speech": response3, "displayText": response3 
	  	//"speech" is the spoken version of the response, "displayText" is the visual version
	  	}));
  	}

  	if (address == "" & (duration.amount == null || duration.unit == null || activity == null)) { 
  		response = "You forgot to enter either the activity or duration, or I wasn't able to understand it. Please try again."
  		res.setHeader('Content-Type', 'application/json'); //Requires application/json MIME type
  		res.send(JSON.stringify({ "speech": response, "displayText": response 
  		//"speech" is the spoken version of the response, "displayText" is the visual version
  		}));
  	}

  	if (duration.unit != "min") { 
  		duration = duration.amount * 60;
  	}
  	else {
  		duration = duration.amount;
  	}

  	if (address == "" & duration != null && activity != null) { 
  		activityFinal = activity
  		durationFinal = duration
  	}

  	//
  	//
  	// USE ACTIVITY AND DURATION BEFORE THIS
  	//
  	//



  	if (address == "") { 
	  	response2 = "What is the address of where you have to go?"
	  	res.setHeader('Content-Type', 'application/json'); //Requires application/json MIME type
		res.send(JSON.stringify({ "speech": response2, "displayText": response2 
 		//"speech" is the spoken version of the response, "displayText" is the visual version
	  	}));
  	}
  	
};

// FIREBASE INIT

var config = {
    apiKey: "AIzaSyC3Ml5v1SXHo91b0flg4OuwFeaIg9SWhx4",
    authDomain: "calndr00.firebaseapp.com",
    databaseURL: "https://calndr00.firebaseio.com",
    projectId: "calndr00",
    storageBucket: "calndr00.appspot.com",
    messagingSenderId: "944701268579"
  };
  firebase.initializeApp(config);


function updateData() {
	var firebaseRef = firebase.database().ref();
	firebaseRef.child("activity").set(activityFinal);
	firebaseRef.child("duration").set(durationFinal);
	firebaseRef.child("address").set(addressFinal);
}
  