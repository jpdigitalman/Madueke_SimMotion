int pwmValues[6];

void serverpage2(){
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = "<html><head>";
        html += "<meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>";
        html += "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'>";
        html += "</head><body class='bg-light text-dark'>";
        html += "<div class='container mt-5'>";
        html += "<div class='card border-primary p-4 mx-auto' style='max-width: 500px;'>";
        html += "<h1 class='text-center mb-4'>MaduekeSim 运动测试</h1>";

        for (int i = 0; i < 6; i++) {
            html += "<div class='card mb-3'>";
            html += "<div class='card-body'>";
            html += "<h5 class='card-title'>Channel " + String(i+1) + "</h5>";
            html += "<input type='text' class='form-control' id='text" + String(i) + "' value='" + String(pwmValues[i]) + "' onchange='updatePWM(this.value, " + String(i) + ")'>";
            html += "<input type='range' class='form-control-range mt-3' id='range" + String(i) + "' min='-5000' max='5000' value='" + String(pwmValues[i]) + "' onchange='updatePWMRange(this.value, " + String(i) + ")'>";
            html += "<small class='form-text text-muted'>Value: <span id='value" + String(i) + "'>" + String(pwmValues[i]) + "</span></small>";
            html += "<small class='form-text text-muted' id='status" + String(i) + "'></small>";
            html += "</div></div>";
        }

        html += "</div></div>";
        html += "<script src='https://code.jquery.com/jquery-3.3.1.slim.min.js'></script>";
        html += "<script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js'></script>";
        html += "<script src='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js'></script>";
        html += "<script>";
        html += "function updatePWM(value, channel) {";
        html += "  document.getElementById('range' + channel).value = value;";
        html += "  var xhttp = new XMLHttpRequest();";
        html += "  xhttp.onreadystatechange = function() {";
        html += "    if (this.readyState == 4 && this.status == 200) {";
        html += "      document.getElementById('value' + channel).innerHTML = value;";
        html += "      if (this.responseText.trim() === 'OK') {";
        html += "        document.getElementById('status' + channel).innerHTML = 'Channel OK';";
        html += "        document.getElementById('status' + channel).style.color = 'blue';";
        html += "      } else {";
        html += "        document.getElementById('status' + channel).innerHTML = 'Channel Error';";
        html += "        document.getElementById('status' + channel).style.color = 'red';";
        html += "      }";
        html += "    }";
        html += "  };";
        html += "  xhttp.open('GET', '/update?channel=' + channel + '&value=' + value, true);";
        html += "  xhttp.send();";
        html += "}";
        html += "function updatePWMRange(value, channel) {";
        html += "  document.getElementById('text' + channel).value = value;";
        html += "  var xhttp = new XMLHttpRequest();";
        html += "  xhttp.onreadystatechange = function() {";
        html += "    if (this.readyState == 4) {";
        html += "      if (this.status == 200) {";
        html += "        document.getElementById('value' + channel).innerHTML = value;";
        html += "        document.getElementById('status' + channel).innerHTML = 'Channel OK';";
        html += "        $('#status' + channel).removeClass('text-muted').css('color', 'blue')";
        html += "      } else {";
        html += "        document.getElementById('value' + channel).innerHTML = value;";
        html += "        document.getElementById('status' + channel).innerHTML = 'Channel Error';";
        html += "        $('#status' + channel).removeClass('text-muted').css('color', 'red')";
        html += "      }";
        html += "    }";
        html += "  };";
        html += "  xhttp.open('GET', '/update?channel=' + channel + '&value=' + value, true);";
        html += "  xhttp.send();";
        html += "}";
        html += "</script></body></html>";

        request->send(200, "text/html", html);
    });

    server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
        String channelParam = request->arg("channel");
        String valueParam = request->arg("value");

        if (channelParam.length() > 0 && valueParam.length() > 0) {
            int channel = channelParam.toInt();
            int value = valueParam.toInt();

            if (channel >= 0 && channel < 6) {
                bool ok_rotate = rotateMotorbyStep(channel+1, value);
                PRINTLINE(!ok_rotate?("Channel " + String(channel+1) + " Error"):("Channel " + String(channel+1) + " Ok"));
                if (ok_rotate) {
                    pwmValues[channel] = value;
                    request->send(200, "text/plain", "OK");
                } else {
                    request->send(500, "text/plain", "Channel Error");
                }
                return;
            }
        }

        request->send(400, "text/plain", "Bad Request");
    });

    server.begin();
}
