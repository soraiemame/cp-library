# generate snippet codes

import glob
import json

def main():
    paths = glob.glob("*.cpp")
    res = {}

    for path in paths:
        with open(path) as file:
            fname = path.replace(".cpp","")
            res[fname] = { "prefix": f"@{fname}" }
            body = []
            for line in file:
                body.append(line.strip("\n"))
            res[fname]["body"] = body
            res[fname]["description"] = fname
    
    with open("snippet.json","w") as out:
        json.dump(res,out,indent=4)
    
    print(json.dumps(res,indent=4))

if __name__ == "__main__":
    main()
