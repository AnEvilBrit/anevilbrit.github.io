let username, gamename;

function userGame(user, game) {
    username = user;
    gamename = game;

    Itch.getGameData({
        user: username,
        game: gamename,
        onComplete: function(data) {
            if (data.links === undefined) {
                document.getElementById("price").innerHTML = "Game not found"
                document.getElementById("buy_button").innerHTML = "View My itch.io Page"
                document.getElementById("buy_button").href = "https://shirwan.itch.io"
                document.getElementById("itch_icon").src = "/images/Cover/GameNotFound.png"
            }
            else {
                document.getElementById("buy_button").href = data.links.self
                if (data.price == null || data.price === "$0.00") {
                    document.getElementById("price").innerHTML = "Price: Free"
                } else {
                    document.getElementById("price").innerHTML = "Price:" + data.price
                }
                document.getElementById("buy_button").innerHTML = "View game on itch!"
                document.getElementById("itch_icon").src = data.cover_image
            }
        }
    })
}