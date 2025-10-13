$(document).ready(function(){
  $.ajax({
    url: "data.php", // location of the datafile
    method: "GET",
    success: function(data) {
      console.log(data);
      var x_axis = []; // a generic variable
      var y_axis = [];

      for(var i in data) {
        x_axis.push("N:" + data[i].time_received); // must match your dBase columns
        y_axis.push(data[i].temperature);
      }

      var chartdata = {
        labels: x_axis,
        datasets : [
          {
            label: 'Temperature of Node_1', //Title
            // Change colors: https://www.w3schools.com/css/tryit.asp?filename=trycss3_color_rgba 
            backgroundColor: 'rgba(0, 255, 0, 0.43)', 
            borderColor: 'rgba(200, 200, 200, 0.75)', 
            hoverBackgroundColor: 'rgba(200, 200, 200, 1)',
            hoverBorderColor: 'rgba(200, 200, 200, 1)',
            data: y_axis
          }
        ]
      };

      var ctx = $("#mycanvas");

      var barGraph = new Chart(ctx, {
        type: 'bar',   //Chart Type 
        data: chartdata,
	options: {
		scales: {
			y: {
				title: {
					display: true,
					text: 'Temperature in Celcius'
				}
			},
			x: {
				title: {
					display: true,
					text: 'Time Received'
				}
			}
		}
	}
      });
    },
    error: function(data) {
      console.log(data);
    }
  });
});
