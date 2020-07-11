#!/usr/bin/env bash

# Infos
ASSET_NAME=SamuelMenu.AppImage
AUTH="-u SamuelGallay:$1"
REPO_NAME=SamuelGallay/SFML-Projects
RELEASE_ID=28456796


# To create a new tag on the last commit
HASH=$(git rev-parse HEAD)
SHORT_HASH=$(git rev-parse HEAD | cut -c 1-7)
JSON=$(cat <<EndOfMessage
{
  "tag": "auto-$SHORT_HASH", 
  "message": "Automatic Tag",
  "object": "$HASH",
  "type": "commit"
}
EndOfMessage
)
curl "$AUTH" -H "Content-Type: application/json" -d "$JSON" "https://api.github.com/repos/$REPO_NAME/git/tags"

# To update the release
JSON=$(cat <<EndOfMessage
{
  "tag_name": "auto-$SHORT_HASH",
  "target_commitish": "master",
  "name": "Latest Release",
  "body": "Last commit : $(date)",
  "draft": false,
  "prerelease": false
}
EndOfMessage
)
curl "$AUTH" -H "Content-Type: application/json" -d "$JSON" "https://api.github.com/repos/$REPO_NAME/releases/$RELEASE_ID"



# To get the asset ID from the asset NAME
# Black magic happens here... (not mine...)
RELEASE_INFO=$(curl -s "$AUTH" "https://api.github.com/repos/$REPO_NAME/releases/$RELEASE_ID")
eval "$(echo "$RELEASE_INFO" | grep -C2 "\"name\": \"$ASSET_NAME\"" | grep -m 1 "id.:" | grep -w id | tr : = | tr -cd '[[:alnum:]]=' | sed 's/id/ASSET_ID/')"

# To delete the asset if already exists
curl "$AUTH" -X "DELETE" "https://api.github.com/repos/$REPO_NAME/releases/assets/$ASSET_ID"

# To upload the new asset
curl "$AUTH" --data-binary @"$2" -H "Content-Type: application/octet-stream" "https://uploads.github.com/repos/$REPO_NAME/releases/$RELEASE_ID/assets?name=$ASSET_NAME"
