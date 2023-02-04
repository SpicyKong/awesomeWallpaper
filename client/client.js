let tmp = `{
    "Development": [
        {"name":"Visual Studio","path":"%%%","icon":"vs.png"},
        {"name":"Visual Studio Code","path":"%%%","icon":"vscode.png"},
        {"name":"Github Desktop","path":"%%%","icon":"github.png"},
        {"name":"GitKraken","path":"%%%","icon":"gitkraken.png"},
        {"name":"Eclipse","path":"%%%","icon":"eclipse.png"}
    ],
    "Games": [
        {"name":"LOL","path":"%%%","icon":"lol.png"},
        {"name":"Minecraft","path":"%%%","icon":"minecraft.png"},
        {"name":"Steam","path":"%%%","icon":"steam.png"}
    ],
    "Others": [
        {"name":"Chrome","path":"%%%","icon":"chrome.png"},
        {"name":"Kakao Talk","path":"%%%","icon":"kakaotalk.png"},
        {"name":"Discord","path":"%%%","icon":"discord.png"},
        {"name":"Notion","path":"%%%","icon":"notion.png"}
    ]
}`

function sendData(name) {
    console.log(name);
}

window.onload = function() {
    var a = document.getElementsByTagName("body");
    a[0].style.width = screen.availWidth+"px";
    a[0].style.height = screen.availHeight+"px";
    console.log(screen.availWidth);
    console.log(screen.availHeight);
    
    let programList = JSON.parse(tmp);
    let wrapper = document.getElementById("wrapper");
    for (var key in programList) {
        var docField = document.createElement('div');
        var docFieldTitle = document.createElement('div');
        docField.setAttribute('class', 'field');
        docFieldTitle.setAttribute('class', 'field-title');
        docFieldTitle.append(key);
        docField.appendChild(docFieldTitle);

        var docApp;
        for (var app of programList[key]) {
            docApp = document.createElement('div');
            var docAppIcon = document.createElement('img');
            var docAppTitle = document.createElement('div');
            docApp.setAttribute("class", "app");
            docApp.setAttribute("ondblclick", "sendData('"+app["name"]+"')");
            docAppIcon.setAttribute("src", "icons/" + app["icon"]);
            docAppTitle.setAttribute("class", "app-title");
            docAppTitle.append(app["name"]);
            
            docApp.appendChild(docAppIcon);
            docApp.appendChild(docAppTitle);
            docField.appendChild(docApp);
        }
        
        wrapper.appendChild(docField);
    }
}
/*
window.wallpaperPropertyListener = {
    applyUserProperties: function(properties) {
        if (properties.customtext) {
            var mySliderValue = properties.customtext.value;
            document.getElementById("bg").innerText=mySliderValue;
            // Do something useful with the value here or assign it to a global variable
        }S
    },S
};*/