// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
const fs = require('fs')
var $ = require("jquery")
const WebSocket = require('ws')

const wss = new WebSocket.Server({ port: 8050 })
let queryNum = 0
 

        // load current chart package
        google.charts.load("current", {
            packages: ["corechart", "line"]
        });
        // set callback function when api loaded
        google.charts.setOnLoadCallback(drawChart);
        function drawChart() {
            // create data object with default value
            var data = google.visualization.arrayToDataTable([
                ["Year", "Esp FreeHeap online"],
                [0, 2650]
            ]);
            // create options object with titles, colors, etc.
            var options = {
                title: "FreeHeap Esp32",
                hAxis: {
                    title: "Time"
                },
                vAxis: {
                    title: "Bytes remaining"
                }
            };
            // draw chart on load
            var chart = new google.visualization.LineChart(
                document.getElementById("chart_div")
            );
            chart.draw(data, options);
            var index = 0;
            
						wss.on('connection', function connection(ws) {
							ws.on('message', function incoming(message) {
								//console.log('received: %s', message);
								// Add chart
								var final =  Number(Math.floor( message / 100));
								console.log(final);
                data.addRow([index,final]);
                chart.draw(data, options);
                index++;								
							});  
						});            
        }
