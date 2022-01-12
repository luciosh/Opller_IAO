
const AWS = require('aws-sdk');
const docClient = new AWS.DynamoDB.DocumentClient();
var id;

var table = "iao_table";
exports.handler = function(event, context, callback) {

	var evento = JSON.stringify(event);
	// event.TableName= table;
	var now = new Date();
	var utc = now.getTime() + (now.getTimezoneOffset() * 60000);
	var now = new Date(utc + (3600000*-4));

	var new_record = {
	TableName: table,
	Item: {
		registry:"", //registry
		device_id:"", //device_id
		umidade:"",
		data:"",
		hora:"",
		}
	}; 
  
  var evento_parse = JSON.parse(evento); 
  var mes = parseInt(now.getMonth()) + 1;
	// transformacao e atribuicao de json para insert
	new_record.Item.device_id = evento_parse.device_id;
	new_record.Item.registry = now.getTime();
	delete evento_parse.device_id;
	new_record.Item.data = now.getDate() + "-" + mes.toString() + "-" + now.getFullYear();
	new_record.Item.hora = now.getHours() + ":" + now.getMinutes() + ":" + now.getSeconds();
	new_record.Item.umidade = evento_parse.umidade;
	id = new_record.Item.device_id;	
	
  if(umidade === undefined){
    send_mqtt_callback('{"message": "erro0" }');
  }else{
    docClient.put(new_record, function(err, data){
      if (err) {
        var evento = JSON.stringify();
        callback(err, null);
        send_mqtt_callback('{"message": "erro1" }');
      }else{
        // send_sns(new_record, err, callback);
        send_mqtt_callback('{"message": "sucesso" }');
        callback(null, data);
      }
    });
  }

	
}

//SEND ENDPOINT MESSAGE
// function send_sns(event, context, callback) {
// 	var params = {
//  		Message: JSON.stringify(event), /* required */
// 		TopicArn: ''
// 	};
// 	// console.log('Received event:', JSON.stringify(event, null, 4));
// 	var publishTextPromise = new AWS.SNS({apiVersion: '2010-03-31'}).publish(params).promise();
// 	callback(null, "Success");
// };


function send_mqtt_callback(message){
	var iotdata = new AWS.IotData({endpoint: 'coloque o endpoint aqui', apiVersion: '2015-05-28'});
 
	var params = {
		topic: "iao/" + id,
		payload: message,
		qos: 0,
	};
 
	iotdata.publish(params, function(err, data) {
		if(err){
			console.log(err);
		}
		else{
			console.log("Success, I guess.");
			//context.succeed();
		}
	});
}
