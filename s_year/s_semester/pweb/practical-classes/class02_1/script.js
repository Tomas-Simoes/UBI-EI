function onSubmit() {
    form = document.getElementById("form")
    var formData = new FormData(form);

    alert("Welcome " + formData.get("name") + "!")

    formData.forEach((value, key) => {
        console.log(key + ": " + value)
    })
}