Itch.getGameData({
    user: "shirwan",
    game: "mushroom-soup",
    onComplete: function(data) {
        var b = document.getElementById("buy_button")
        b.href = data.links.self
        var p = document.getElementById("price")
        p.innerHTML = data.price
        var i = document.getElementById("itch_icon")
        i.src = data.cover_image
        console.log(data)
    }
})