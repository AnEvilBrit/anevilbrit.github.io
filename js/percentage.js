function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function percent(num, id, totalDuration) {
    let updatesPerSecond = 60;
    let delayTime = 1000 / updatesPerSecond; // 1 second / 30 updates = ~33.33ms delay
    let increment = num / (totalDuration / delayTime); // Calculate the increment for each update

    for(let i = 0; i <= num; i += increment){
        await delay(delayTime);
        let element = document.getElementById(id);
        if (element) {
            element.textContent = Math.round(i) + "%";
        }
        let elementBar = document.getElementById(id + "Bar")
        if (elementBar) {
            elementBar.style.width = Math.round(i) + "%";
        }
    }

    // Ensure that the progress bar is set to 100% when the function finishes
    let element = document.getElementById(id);
    if (element) {
        element.textContent = num + "%";
    }
    let elementBar = document.getElementById(id + "Bar")
    if (elementBar) {
        elementBar.style.width = num + "%";
    }
}

let totalDuration = 2250; // 2 seconds
percent("100","qubicle", totalDuration);
percent("90","ue5", totalDuration);
percent("85","blender", totalDuration);
percent("85","photoshop", totalDuration);
percent("75","substance", totalDuration);
percent("45","aseprite", totalDuration);
percent("10","godot", totalDuration);
percent("90","ueblueprints", totalDuration);
percent("80","html", totalDuration);
percent("70","python", totalDuration);
percent("60","css", totalDuration);
percent("30","cpp", totalDuration);
percent("25","js", totalDuration);
percent("15","cs", totalDuration);