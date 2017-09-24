/*
* HTTP Cloud Function.
*
* @param {Object} req Cloud Function request context.
* @param {Object} res Cloud Function response context.
*/

exports.CaLNDR = function CaLNDR (req, res) {

  	let activity = req.body.result.parameters['activity']
  	let duration = req.body.result.parameters['duration']
  	let address = req.body.result.parameters['address']

  	if (address == "" & (duration.amount == null || duration.unit == null || activity == null)) { 
  		response = "You forgot to enter either the activity or duration, or I wasn't able to understand it. Please try again."
  		res.setHeader('Content-Type', 'application/json'); //Requires application/json MIME type
  		res.send(JSON.stringify({ "speech": response, "displayText": response 
  		//"speech" is the spoken version of the response, "displayText" is the visual version
  		}));
  	}

  	if (duration.unit = 'h') { 
  		duration = duration.amount * 60;
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

  	if (address != "") {
	  	response3 = "Ok, I am computing an optimized schedule. Please wait..." 
	  	res.setHeader('Content-Type', 'application/json'); //Requires application/json MIME type
	  	res.send(JSON.stringify({ "speech": response3, "displayText": response3 
	  	//"speech" is the spoken version of the response, "displayText" is the visual version
	  	}));
  	}
  	
};