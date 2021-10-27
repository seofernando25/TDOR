from typing import cast
import sounddevice as sd
import soundfile as sf
import threading
import numpy as np
import os

event = threading.Event()


# Open audio file

# Loads all wav files in the directory except _test.wav and output.wav
line = " haha you fell for my trap now ill main his main loadout and domintae the rest of the tf2 comunity bwahahahaha "
line = line.lower()


def load_wav_files():
    wav_files = []
    for file in os.listdir("./"):
        if file.endswith(".wav"):
            if file != "_test.wav" and file != "output.wav":
                wav_files.append(file.removesuffix(".wav"))
    return wav_files


phonems = load_wav_files()
print(phonems)
# Remove adjacent letters
# example:
# aabb -> ab
# afternoon -> afternon
# cats -> cats


def remove_adjacent(line):
    new_line = ""
    for i in range(len(line)):
        if i == 0:
            new_line += line[i]
        elif line[i] != line[i-1]:
            new_line += line[i]
    return new_line


def remove_non_vowels(line):
    line = line.lower()
    vowels = "aeiou"
    ret = ""
    for char in line:
        if (char not in vowels) and (char not in [" ", ".", ",", "!", "?"]):
            continue
        ret += char
    return ret


line = line.replace(".", ".")
line = line.replace(",", ".")
line = line.replace("?", ".")

# line = remove_non_vowels(line)
# line = remove_adjacent(line)
line = line.replace("ck", "k")
line = line.replace("ph", "f")
line = line.replace("qu", "k")
line = line.replace("q", "k")
line = line.replace("cing", "sing")
line = line.replace(" the ", " da ")
line = line.replace(" own ", " oen")
line = line.replace("dis", "ds")
line = line.replace(" say ", " sae")
line = line.replace(" you ", " yu ")

line = line.replace(" was ", " wos ")

line = line.replace("this", "ds")
line = line.replace("over", "oever")
line = line.replace("lazy", "laezy")
line = line.replace("c", "k")
line = line.replace(" kh", " ch")  # Revert words starting with ch eg: champ

line = line.replace(" my ", " mie ")
line = line.replace(" i ", " ie ")

print(line)
lines_left = line

data = np.zeros(shape=(1, 1))
fs = 44100

while lines_left != "":
    if lines_left[0] in [" ", ",", ".", "?"]:
        if data is None:
            lines_left = lines_left[1:]
            continue

        mul = 1
        if lines_left[0] == " ":
            mul = 0.01
        _data = np.zeros(shape=(int(fs*mul), 1))
        lines_left = lines_left[1:]
    else:
        chars_to_read = 1

        next_char = ""
        for x in range(4):
            w = lines_left[:x]
            if w in phonems:
                next_char = w
        chars_to_read = len(next_char)

        if next_char == "":
            print(f"Found no matching sound for ", lines_left[0])
            lines_left = lines_left[1:]
            continue
        lines_left = lines_left[chars_to_read:]
        print(next_char)
        try:
            _data, _ = sf.read(next_char + ".wav", always_2d=True)
        except:
            print(f"File for sound {next_char} not found")
            continue

    data = np.concatenate((data, _data))

current_frame = 0


def callback(outdata, frames, _, status):
    global current_frame
    if status:
        print(status)
    chunksize = min(len(data) - current_frame, frames)
    outdata[:chunksize] = data[current_frame:current_frame + chunksize]
    if chunksize < frames:
        outdata[chunksize:] = 0
        raise sd.CallbackStop()
    current_frame += chunksize


# sd.play(data, fs, blocking=True)
sample_mul = 1
stream = sd.OutputStream(
    samplerate=fs*sample_mul, channels=data.shape[1],
    callback=callback, finished_callback=event.set)
with stream:
    event.wait()

sf.write("output.wav", data, int(fs*sample_mul), 'PCM_24')
