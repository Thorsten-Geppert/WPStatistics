function loadData() {
    var req = new XMLHttpRequest();
    
    req.onreadystatechange = function() {
        if(req.readyState === XMLHttpRequest.DONE) {
            if(req.status === 200) {
                var root = JSON.parse(req.responseText);
                                
                headlineLabel.text = root.websiteName;
                entriesListModel.append(root.entries);
            } else {
                errorPopup.visible = true;
            }
        }
    }
    
    req.open("GET", "http://statistics.tgeppert.gg/?action=json");
    req.send();
}
