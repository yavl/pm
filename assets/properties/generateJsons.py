import json

data = {
	"window": {
		"width": 800,
		"height": 600,
		"title": "Trewlib"
	}
}

with open("properties.json", "w") as f:
	json.dump(data, f, indent=4)