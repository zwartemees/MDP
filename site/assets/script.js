'use strict'
import { getCurrendSlide, setCurrendSlide } from "./javascript/cookie.js"

window.onload = () => {

    var refLinks = document.getElementsByClassName("refLink");
    for (let index = 0; index < refLinks.length; index++) {
        refLinks[index].addEventListener("click", function () {
            showRefrenceSlide();
        });
    }
    var divs = document.getElementsByTagName("div")

    for (let index = 0; index < divs.length; index++) {
        var images = divs[index].getElementsByTagName('img')
        if (images.length > 0 && divs[index].className != "slide") {
            for (let index2 = 0; index2 < images.length; index2++) {
                if (images[index2].parentNode == divs[index]) {
                    divs[index].className = "imageContainer";
                }
            }
        }
    }


    setCurrendSlide(0)
    hideSlides()
}


window.onmousedown = () => {
    //nextDia()
}
window.onkeyup = (event) => {
    let code = event.keyCode
    if (code == 37) {
        previoseDia()
        window.scrollTo(0, 0);
    } else if (code == 39 || code == 13 || code == 32) {
        nextDia()
        window.scrollTo(0, 0);
    }

}
function showRefrenceSlide() {
    var slides = document.getElementsByClassName("slide");
    for (let index = 0; index < slides.length; index++) {
        slides[index].style.visibility = 'hidden';
    }
    document.getElementById("refrences").style.visibility = "visible";
    setCurrendSlide(getCurrendSlide() - 1);

}

function hideSlides() {
    var currentDiaNumber = getCurrendSlide()
    var slides = document.getElementsByClassName("slide");
    for (let index = 0; index < slides.length; index++) {
        slides[index].style.visibility = 'hidden';
    }
    slides[currentDiaNumber].style.visibility = "visible";
}
function previoseDia() {

    hideRefrences()
    var slides = document.getElementsByClassName("slide");
    var currentDiaNumber = getCurrendSlide()
    if (currentDiaNumber > 0) {

        slides[currentDiaNumber].style.visibility = 'hidden';
        slides[currentDiaNumber - 1].style.visibility = "visible";

        currentDiaNumber -= 1
    } else {
        currentDiaNumber = 0
    }

    setCurrendSlide(currentDiaNumber)
}


function nextDia() {

    hideRefrences()
    var slides = document.getElementsByClassName("slide");
    var currentDiaNumber = getCurrendSlide()
    if (currentDiaNumber < slides.length - 1) {
        slides[currentDiaNumber].style.visibility = 'hidden';
        slides[currentDiaNumber + 1].style.visibility = "visible";


        currentDiaNumber += 1
    } else {
        currentDiaNumber = slides.length - 1
    }

    setCurrendSlide(currentDiaNumber)
}

function hideRefrences() {
    let refSlide = document.getElementById("refrences")
    if (refSlide != null) {
        refSlide.style.visibility = "hidden"
    }

}
