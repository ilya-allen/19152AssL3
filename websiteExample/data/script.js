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
