
const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>HydroSmart</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
    }
    .pwmValuelider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
  
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>

  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">HydroSmart</div>
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">DATE</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>
            
          </div>
      </div>
    </header>
  

</header>
<div id="logoContainer"></div>
  
    <main class="container" style="margin-top:70px">
      <div class="category">Effluent Treatment Parameters</div>
      <div style="border-radius: 10px !important;">
      <table style="width:50%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <tr>
        <th colspan="1"><div class="heading">Data</div></th>
        <th colspan="1"><div class="heading">Level</div></th>
      </tr>
      <tr>
        <td><div class="bodytext">Shade</div></td>
        <td><div class="tabledata" id = "b0"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">distance(cm)</div></td>
        <td><div class="tabledata" id = "b1"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">Effluent flowrate(Litres/Min)</div></td>
        <td><div class="tabledata" id = "f1"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">PAC flowrate(Litres/Min)</div></td>
        <td><div class="tabledata" id = "t1"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">DC flowrate(Litres/Min)</div></td>
        <td><div class="tabledata" id = "t2"></div></td>
      </tr>
      <tr>
        <td><div class="bodytext">CAT flowrate(Litres/Min)</div></td>
        <td><div class="tabledata" id = "t3"></div></td>
      </tr>
      </table>
    </div>
    <br>
    <div class="category">Flow Controls</div>
    <br>
    <br>
    <div class="bodytext">Pump Speed</div>
    <button type="button" class = "btn" id = "btn1" onclick="ButtonPress1()">Toggle</button>
    </div>
    <br>
    <br>
    <div class="bodytext">Water flow control (pwmValue: <span id="pwmValue"></span>)</div>
    <br>
    <input type="range" class="fanrpmslider" min="0" max="255" value = "0" width = "0%" oninput="UpdateSlider(this.value)"/>
    <br>
    <br>
  </main>

  <footer div class="foot" id = "temp" >One drop at a time.</div></footer>
  
  </body>


  <script type = "text/javascript">
  
    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }

    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress0() {
      var xhttp = new XMLHttpRequest(); 
      var message;
      // if you want to handle an immediate reply (like status from the ESP
      // handling of the button press use this code
      // since this button status from the ESP is in the main XML code
      // we don't need this
      // remember that if you want immediate processing feedbac you must send it
      // in the ESP handling function and here
      /*
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          message = this.responseText;
          // update some HTML data
        }
      }
      */
       
      xhttp.open("PUT", "BUTTON_0", false);
      xhttp.send();
    }


    // function to handle button press from HTML code above
    // and send a processing string back to server
    // this processing string is use in the .on method
    function ButtonPress1() {
      var xhttp = new XMLHttpRequest(); 
      /*
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("button1").innerHTML = this.responseText;
        }
      }
      */
      xhttp.open("PUT", "BUTTON_1", false);
      xhttp.send(); 
    }
    
    function UpdateSlider(value) {
      var xhttp = new XMLHttpRequest();
      // this time i want immediate feedback to the fan speed
      // yea yea yea i realize i'm computing fan speed but the point
      // is how to give immediate feedback
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          // update the web based on reply from  ESP
          document.getElementById("fanrpm").innerHTML=this.responseText;
        }
      }
      // this syntax is really weird the ? is a delimiter
      // first arg UPDATE_SLIDER is use in the .on method
      // server.on("/UPDATE_SLIDER", UpdateSlider);
      // then the second arg VALUE is use in the processing function
      // String t_state = server.arg("VALUE");
      // then + the controls value property
      xhttp.open("PUT", "UPDATE_SLIDER?VALUE="+value, true);
      xhttp.send();
    }

    // function to handle the response from the ESP
    function response(){
      var message;
      var barwidth;
      var currentsensor;
      var xmlResponse;
      var xmldoc;
      var dt = new Date();
      var color = "#e8e8e8";
     
      // get the xml stream
      xmlResponse=xmlHttp.responseXML;
  
      // get host date and time
      document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString();
  
      // A0
      xmldoc_1 = xmlResponse.getElementsByTagName("B0"); //bits for A0
      message_1 = xmldoc_1[0].firstChild.nodeValue;
      
      if (message_1 > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      
      barwidth = message_1 / 5;
      document.getElementById("b0").innerHTML=message_1;
      document.getElementById("b0").style.width=(barwidth+"%");
  
  
      // A1
      xmldoc_2 = xmlResponse.getElementsByTagName("B1");
      message_2 = xmldoc_2[0].firstChild.nodeValue;

      if (message_2 > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      
      barwidth = message_2 / 5;
      document.getElementById("b1").innerHTML=message_2;
      document.getElementById("b1").style.width=(barwidth+"%");
      
      //effflow
      xmldoc_3 = xmlResponse.getElementsByTagName("F1"); //bits for A0
      message_3 = xmldoc_3[0].firstChild.nodeValue;
      
      if (message_3 > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      
      barwidth = message_3 / 6;
      document.getElementById("f1").innerHTML=message_3;
      document.getElementById("f1").style.width=(barwidth+"%");

      //pac
      xmldoc_4 = xmlResponse.getElementsByTagName("T1");
      message_4 = xmldoc_2[0].firstChild.nodeValue;

      if (message_4 > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      
      barwidth = message_4 / 6;
      document.getElementById("t1").innerHTML=message_2;
      document.getElementById("t1").style.width=(barwidth+"%");

      //dc
      xmldoc_5 = xmlResponse.getElementsByTagName("T2");
      message_5 = xmldoc_2[0].firstChild.nodeValue;

      if (message_5 > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      
      barwidth = message_5 / 6;
      document.getElementById("t2").innerHTML=message_2;
      document.getElementById("t2").style.width=(barwidth+"%");
      
      //cat
      xmldoc_6 = xmlResponse.getElementsByTagName("T3");
      message_6 = xmldoc_2[0].firstChild.nodeValue;

      if (message_6 > 2048){
      color = "#aa0000";
      }
      else {
        color = "#0000aa";
      }
      
      barwidth = message_6 / 6;
      document.getElementById("t3").innerHTML=message_2;
      document.getElementById("t3").style.width=(barwidth+"%");

      xmldoc = xmlResponse.getElementsByTagName("LED");
      message = xmldoc[0].firstChild.nodeValue;
  
      if (message == 0){
        document.getElementById("btn0").innerHTML="Turn ON";
      }
      else{
        document.getElementById("btn0").innerHTML="Turn OFF";
      }
         
      xmldoc = xmlResponse.getElementsByTagName("SWITCH");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("switch").style.backgroundColor="rgb(200,200,200)";
      // update the text in the table
      if (message == 0){
        document.getElementById("switch").innerHTML="Switch is OFF";
        document.getElementById("btn1").innerHTML="Turn ON";
        document.getElementById("switch").style.color="#0000AA"; 
      }
      else {
        document.getElementById("switch").innerHTML="Switch is ON";
        document.getElementById("btn1").innerHTML="Turn OFF";
        document.getElementById("switch").style.color="#00AA00";
      }
     }
  
    // general processing code for the web page to ask for an XML steam
    // this is actually why you need to keep sending data to the page to 
    // force this call with stuff like this
    // server.on("/xml", SendXML);
    // otherwise the page will not request XML from the ESP, and updates will not happen
    function process(){
     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",100);
    }
  
  
  </script>

</html>



)=====";