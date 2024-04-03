var timeout;
function changeText() {
    if (document.hidden) {
    } else {
        var elem = document.getElementById("change");
        elem.innerHTML = 'print("My Portfolio")';
        elem.className = "animate__animated animate__fadeOut";
        clearTimeout(timeout);
        timeout = setTimeout(function () {
            elem.innerHTML = "My Portfolio";
            elem.className = "animate__animated animate__fadeIn";
        }, 2000);
    }
}