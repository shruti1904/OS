function sendData()
{
	
	var xhttpRequest = new XMLHttpRequest();

	xhttpRequest.onreadystatechange = function(){
		if(this.readyState == 4 && this.status == 200){
			var data = this.responseText;

		}
	};
	var x = checkFeedback();
	console.log(x);
	xhttpRequest.open("GET",'localhost/itsa/FeedbackForm/feedback.php?stars="+x"',"true");
	xhttpRequest.send();
}

function checkFeedback()
{
	if(document.getElementById('star-5').checked){
		console.log(2);
		return 2;
	}
	else if(document.getElementById('star-4').checked){
		console.log(1);
		return 1;
	}
	else if(document.getElementById('star-3').checked){
		console.log(0);
		return 0;

	}
	else if(document.getElementById('star-2').checked){
		console.log(-1);
		return -1;
	}
	else if(document.getElementById('star-1').checked){
		console.log(-2);
		return -2;
	}

}