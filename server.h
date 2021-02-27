const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP Web Server</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 360px; height: 25px; background: #FFD65C;
      outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background: #003249; cursor: pointer;}
    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #003249; cursor: pointer; } 
  </style>
</head>
<body>
  <h2>Ventilador Mecanico</h2>
  <h3>Miguel Quispe</h3>
  <p></p>
  <p><label>Volumen : <span id="Volumen">%VOLUMENSLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateSliderVolumen(this)" id="VolumenSlider" min="0" max="750" value="%VOLUMENSLIDERVALUE%" step="1" class="slider"></p>
  <p><label>Frecuencia : <span id="Frecuencia">%FRECUENCIASLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateSliderFrecuencia(this)" id="FrecuenciaSlider" min="0" max="750" value="%FRECUENCIASLIDERVALUE%" step="1" class="slider"></p>
<script>
function updateSliderVolumen(element) {
  var Volumen = document.getElementById("VolumenSlider").value;
  document.getElementById("Volumen").innerHTML = Volumen;
  console.log(Volumen);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value="+Volumen, true);
  xhr.send();
}
function updateSliderFrecuencia(element) {
  var Frecuencia = document.getElementById("FrecuenciaSlider").value;
  document.getElementById("Frecuencia").innerHTML = Frecuencia;
  console.log(Frecuencia);
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/slider?value="+Frecuencia, true);
  xhr.send();
}

</script>
</body>
</html>
)rawliteral";

String processor(const String& var){
  //Serial.println(var);
  if (var == "FRECUENCIASLIDERVALUE"){
    return sliderValue;
  }
  else if (var == "VOLUMENSLIDERVALUE"){
    return sliderValue;
  }
  return String();
}


void server_init(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      volumen = sliderValue.toInt();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
  // Start server
  server.begin();
}
