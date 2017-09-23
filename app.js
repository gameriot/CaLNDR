app.get('/webhook', function(req, res) {
  if (req.query['hub.mode'] === 'subscribe' &&
      req.query['hub.verify_token'] === <"EAAHMv9mv6T4BAGKNp0WnYzQZCgZCtXmLGzdyp65qHUkYwPTsEEdPXGFSZBmudy3IZBre0stelhhOZAp3GfqFcgoTgUzXTfoJZC7Xv4BT0lpJZCu6ylhhseiiZBSyRqsRALr960gZBSazyCUAWGU9QBHLNZBLS4y6FbRxue1L9e9xx98AZDZD">) {
    console.log("Validating webhook");
    res.status(200).send(req.query['hub.challenge']);
  } else {
    console.error("Failed validation. Make sure the validation tokens match.");
    res.sendStatus(403);          
  }  
});