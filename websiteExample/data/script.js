// Below is a function declaration. The function declaration does not have any parameters
function handleNavBar() {
    // store the css element in a javascript varable. This allows the element to be adjusted and accessed in a JS script.
    var x = document.getElementById("myTopnav");
    // if the name of the class of the TopNav is called "topnav" then add the class "responsive" into its name, otherwise change it topnav
    if (x.className === "topnav") {
        x.className += " responsive";
    } else {
        x.className = "topnav";
    }
} 
//---------------------------------------------------------------
//What do these variable and functions have to do with the temperature reading?
window.addEventListener('load', getReadings);
// Function to get current readings on the web page when it loads for the first time
function getReadings() {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) { //4 and 200 mean ready and ok
            var myObj = JSON.parse(this.responseText);
            console.log(myObj);
            document.getElementById("pres").innerHTML = myObj.pressure;
        }
    };
    xhr.open("GET", "/readings", true); 
    xhr.send();
}
// Create an Event Source to listen for events
if (!!window.EventSource) {
    var source = new EventSource('/events');
    source.addEventListener('open', function (e) {
        console.log("Events Connected");
    }, false);
    source.addEventListener('error', function (e) {
        if (e.target.readyState != EventSource.OPEN) {
            console.log("Events Disconnected");
        }
    }, false);
    source.addEventListener('new_readings', function (e) {
        console.log("new_readings", e.data);
        var obj = JSON.parse(e.data);
        document.getElementById("pres").innerHTML = obj.pressure;
    }, false);
}
