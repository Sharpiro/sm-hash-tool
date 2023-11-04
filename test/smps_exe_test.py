import subprocess


def hash(input: str):
    return subprocess.run(
        f'SMPS4HashTool.exe "{input}"',
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    ).stdout


def test_asset_hashes():
    file = open("AssetHashes.txt", "r")
    results = file.read().strip().split("\n")
    temp = [v.split(",") for v in results]

    bad_hash_lines = {143768, 348951, 358992}

    start = 0
    # end =
    for [i, [name, expected_hash]] in list(enumerate(temp))[start:]:
        if i + 1 in bad_hash_lines:
            print("skipping", i + 1)
            continue
        result = hash(name)
        print(i + 1, f"'{name[:40]}...'", expected_hash, result)
        assert result == expected_hash


# print(hash("b\0"))
assert hash("0") == "9625851156722893451"
assert hash("1") == "12204323496446760272"
assert hash("0 1") == "10631490009105291249"
assert hash("alwaysbeclosing") == "12676152422457307961"
assert hash("always be closing") == "10638241236223618570"
assert hash("aa") == "10858719388638484620"
assert hash("a/a") == "13275144271646325503"
assert hash("a//a") == "13275144271646325503"
assert hash("a/\\a") == "13275144271646325503"
assert hash("a/a/") == "13275144271646325503"
assert hash("/a/a") == "13275144271646325503"
assert (
    hash(
        r"models\manmade_system\fencing_pipes_vents\ml_corrogated_metal_fence_01_nopoles.model"
    )
    == "10039806796442441106"
)
assert (
    hash(
        r"models\manmade_system\fencing_pipes_vents\ml_corrogated_metal_fence_01.model"
    )
    == "9910286909319129036"
)
assert (
    hash(
        r"characters\hero\hero_spiderman\animations\vehicle\vehicle_car_passenger_firing_thug_a.animclip"
    )
    == "12326074479071120678"
)


test_asset_hashes()
