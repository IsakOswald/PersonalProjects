const APIKEY = "Don't worry, i'm not that dumb :)"; //Need to learn back-end for secure API calls.
const selectedCity = document.getElementById("citySelect");
const selectButton = document.getElementById("selectButton");
const weatherDisplay = document.getElementById("weatherDisplay");

selectButton.addEventListener("click", () => {
    const userSelect = selectedCity.value;

    if (userSelect === "Select a City Here!") {
        weatherDisplay.innerHTML = `
            <h3 class="weatherStats">Select a City!</h3>
        `;
        return;
    }

    weatherDisplay.innerHTML = `<p class="weatherStats">Fetching from API...</p>`;

    fetch(`https://api.weatherapi.com/v1/current.json?key=${APIKEY}&q=${userSelect}`)
        .then((recieved) => {
            if (!recieved.ok) {
                throw new Error("Error on Request");
            }
            return recieved.json();
        })
        .then((data) => {
            const newHTML = `
                <h3 class="weatherHeading">${data.location.name}, ${data.location.region}, ${data.location.country}</h3>
                <p class="weatherStats">${data.current.condition.text}</p>
                <img src="${data.current.condition.icon}" class="icons">
                <p class="weatherStats">Temperature: ${data.current.temp_c} degrees</p>
                <p class="weatherStats"> Feels like: ${data.current.feelslike_c} degrees </p>
                <p class="weatherStats">Wind Speed: ${data.current.wind_kph} kph </p>
                <p class="weatherStats">Humidity: ${data.current.humidity} </p>
            `;

            weatherDisplay.innerHTML = newHTML;
        })
        .catch((error) => {
            weatherDisplay.innerHTML = `
            <h1>ERROR: ${error}</h1>
            `;
        });
});
