import json
import unicodedata

def remove_accents(text):
    return ''.join(
        c for c in unicodedata.normalize('NFD', text)
        if unicodedata.category(c) != 'Mn'
    )

def normalize(obj):
    if isinstance(obj, str):
        return remove_accents(obj)
    elif isinstance(obj, list):
        return [normalize(x) for x in obj]
    elif isinstance(obj, dict):
        return {k: normalize(v) for k, v in obj.items()}
    else:
        return obj

with open("cards.json", "r", encoding="utf-8") as f:
    data = json.load(f)

cleaned = normalize(data)

with open("cards_clean.json", "w", encoding="utf-8") as f:
    json.dump(cleaned, f, ensure_ascii=True, indent=2)
