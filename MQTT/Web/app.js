$(document).ready(function(){
  $.ajax({
    url: "data.php", // location of the datafile
    method: "GET",
    success: function(data) {
      console.log(data);
      var x_axis = []; // a generic variable
      var y_axis = [];

      for(var i in data) {
        x_axis.push("N:" + data[i].time); // must match your dBase columns
        y_axis.push(data[i].volts);
      }

      var chartdata = {
        labels: x_axis,
        datasets : [
          {
            label: 'Volts Read from Potentiometer', //Title
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
        type: 'line',   //Chart Type 
        data: chartdata,
	options: {
		scales: {
			y: {
				title: {
					display: true,
					text: 'Volts'
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
