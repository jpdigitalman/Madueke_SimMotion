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
            html += "<h5 class='card-title'>Channel " + String(i) + "</h5>";
            html += "<input type='text' class='form-control' id='text" + String(i) + "' value='" + String(pwmValues[i]) + "' onchange='updatePWM(this.value, " + String(i) + ")'>";
            html += "<input type='range' class='form-control-range mt-3' id='range" + String(i) + "' min='-5000' max='5000' value='" + String(pwmValues[i]) + "' onchange='updatePWMRange(this.value, " + String(i) + ")'>";
            html += "<small class='form-text text-muted'>Value: <span id='value" + String(i) + "'>" + String(pwmValues[i]) + "</span></small>";
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
        html += "  xhttp.open('GET', '/update?channel=' + channel + '&value=' + value, true);";
        html += "  xhttp.send();";
        html += "  document.getElementById('value' + channel).innerHTML = value;";
        html += "}";
        html += "function updatePWMRange(value, channel) {";
        html += "  document.getElementById('text' + channel).value = value;";
        html += "  var xhttp = new XMLHttpRequest();";
        html += "  xhttp.open('GET', '/update?channel=' + channel + '&value=' + value, true);";
        html += "  xhttp.send();";
        html += "  document.getElementById('value' + channel).innerHTML = value;";
        html += "}";
        html += "</script></body></html>";

        request->send(200, "text/html", html);
    });

    /*
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = "<html><body>";
        html += "<h1>MaduekeSim 运动测试</h1>";
        for (int i = 0; i < 6; i++) {
            html += "<p>Channel " + String(i) + ": <input type='range' min='0' max='5000' value='" + String(pwmValues[i]) + "' onchange='updatePWM(this.value, " + String(i) + ")'> <span id='value" + String(i) + "'>" + String(pwmValues[i]) + "</span></p>";
        }
        html += "<script>function updatePWM(value, channel) {var xhttp = new XMLHttpRequest(); xhttp.open('GET', '/update?channel=' + channel + '&value=' + value, true); xhttp.send(); document.getElementById('value' + channel).innerHTML = value;}</script></body></html>";
        request->send(200, "text/html", html);
    });
    */
    server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
        String channelParam = request->arg("channel");
        String valueParam = request->arg("value");

        if (channelParam.length() > 0 && valueParam.length() > 0) {
            int channel = channelParam.toInt();
            int value = valueParam.toInt();

            if (channel >= 0 && channel < 6) {  //if (channel >= 0 && channel < 6 && value >= 0 && value <= 5000)
                pwmValues[channel] = value;
                //ledcWrite(channel, map(value, 0, 5000, 0, 255));
                rotateMotorbyStep(channel+1, value);
                //rotateMotorbyStep(channel+1, map(value, -5000, 5000, 0, 10000));
                request->send(200, "text/plain", "OK");
                return;
            }
        }

        request->send(400, "text/plain", "Bad Request");
    });

    server.begin();
}