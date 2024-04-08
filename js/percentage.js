function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function percent(num, id, totalDuration) {
    let delayTime = totalDuration / num;
    for(let i = 0; i <= num; i++){
        await delay(delayTime);
        let element = document.getElementById(id);
        if (element) {
            element.textContent = i + "%";
        }
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