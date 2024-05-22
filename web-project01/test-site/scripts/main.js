let myImage = document.querySelector("img");

myImage.onclick = function() {
    let mySrc = myImage.getAttribute("src");
    if (mySrc === "images/Google_Earth_logo.svg") {
        myImage.setAttribute("src", "images/Google-logo.png");
    } else {
        myImage.setAttribute("src", "images/Google_Earth_logo.svg");
    }
};

let myButton = document.querySelector("button");
let myHeading = document.querySelector("h1");

function setUserName() {
    let myName = prompt("Please enter your name");
    if (!myName || myName === null){
        setUserName();
    }else{
        localStorage.setItem("name", myName);
        myHeading.innerHTML = "반갑습니다, " + myName + "님."; 
    }
}

if(!localStorage.getItem("name")){
    setUserName();
} else {
    let storedName = localStorage.getItem("name");
    myHeading.textContent = "반갑습니다, " + storedName + "님.";
}

myButton.onclick = function(){
    setUserName();
};
