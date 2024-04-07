let username, gamename;

function userGame(user, game) {
    username = user;
    gamename = game;

    Itch.getGameData({
        user: username,
        game: gamename,
        onComplete: function(data) {
            document.getElementById("buy_button").href = data.links.self
            if (data.price == null || data.price === "$0.00") {
                document.getElementById("price").innerHTML = "Price: Free"
            } else {
                document.getElementById("price").innerHTML = "Price:" + data.price
            }
            document.getElementById("itch_icon").src = data.cover_image
            console.log(data)
        }
    })
}