import os
import numpy as np
import PIL
import matplotlib.pyplot as plt
import pandas as pd
import csv
import glob


def readTrafficSigns(rootpath):
    labels = []  # corresponding labels
    # loop over all 42 classes
    for c in range(0, 43):
        prefix = rootpath + '\\' + format(c, '05d') + '\\'  # subdirectory for class
        gtFile = open(prefix + 'GT-' + format(c, '05d') + '.csv')  # annotations file
        gtReader = csv.reader(gtFile, delimiter=';')  # csv parser for annotations file
        next(gtReader)  # skip header
        # loop over all images in current annotations file
        for row in gtReader:
            labels.append(row[7])  # the 8th column is the label
        gtFile.close()
        print(format(c, '03d') + "sort done Lenth is " + len(labels))
    return labels


def save_label_to_npy(training_path=
                      "D:\\dataset\\GTRSB\\GTRSB_Final_Training_Images\\GTSRB\\Final_Training\\Images",
                      npy_path="D:\\dataset\\GTRSB\\"):
    labels = readTrafficSigns(training_path)
    label_array = np.array(labels)
    label_array_int = np.core.defchararray.strip(label_array, '()').astype(int)
    np.save(npy_path + "label.npy", label_array_int)


def convert_train_data(file_dir, jpg_dir='D:\\dataset\\GTRSB\\GTSRB_Final_Training_Images_roi_jpg'):
    directories = [file for file in os.listdir(file_dir) if os.path.isdir(os.path.join(file_dir, file))]
    # print(directories)
    # directories are lists below：
    # ['00000', '00001', '00002', '00003', '00004', '00005', '00006',
    #  '00007', '00008', '00009', '00010', '00011','00012', '00013',
    #  ...

    for files in directories:
        path = os.path.join(jpg_dir, files)
        if not os.path.exists(path):
            os.makedirs(path)

        data_dir = os.path.join(file_dir, files)
        file_names = [os.path.join(data_dir, f) for f in os.listdir(data_dir) if f.endswith(".ppm")]
        for f in os.listdir(data_dir):
            if f.endswith(".csv"):
                csv_dir = os.path.join(data_dir, f)

        csv_data = pd.read_csv(csv_dir)
        # csv_data is a data-frame

        csv_data_array = np.array(csv_data)

        for i in range(csv_data_array.shape[0]):
            csv_data_list = np.array(csv_data)[i, :].tolist()[0].split(";")
            sample_dir = os.path.join(data_dir, csv_data_list[0])
            img = PIL.Image.open(sample_dir)
            box = (int(csv_data_list[3]), int(csv_data_list[4]), int(csv_data_list[5]), int(csv_data_list[6]))
            roi_img = img.crop(box)
            new_dir = os.path.join(path, csv_data_list[0].split(".")[0] + ".jpg")
            roi_img.save(new_dir, 'JPEG')


def convert_test_data(file_dir, jpg_dir='D:\\dataset\\GTRSB\\GTSRB_Final_Test_Images_roi_jpg'):
    for f in os.listdir(file_dir):
        if f.endswith(".csv"):
            csv_dir = os.path.join(file_dir, f)
    csv_data = pd.read_csv(csv_dir)
    csv_data_array = np.array(csv_data)
    for i in range(csv_data_array.shape[0]):
        csv_data_list = np.array(csv_data)[i, :].tolist()[0].split(";")
        sample_dir = os.path.join(file_dir, csv_data_list[0])
        img = PIL.Image.open(sample_dir)
        box = (int(csv_data_list[3]), int(csv_data_list[4]), int(csv_data_list[5]), int(csv_data_list[6]))
        roi_img = img.crop(box)
        new_dir = os.path.join(jpg_dir, csv_data_list[0].split(".")[0] + ".jpg")
        roi_img.save(new_dir, 'JPEG')


def convertRGB2L(jpgfile, outdir, width=32, height=32):
    img = PIL.Image.open(jpgfile)
    try:
        new_img_32 = img.resize((width, height), PIL.Image.BILINEAR)
        new_img = new_img_32.convert('L')
        new_img.save(os.path.join(outdir, os.path.basename(jpgfile)))
    except Exception as e:
        print(e)


def save_L_to_npy(jpgfile, outdir, width=32, height=32):
    img = PIL.Image.open(jpgfile)
    try:
        new_img_32 = img.resize((width, height), PIL.Image.BILINEAR)
        new_img = new_img_32.convert('L')
        new_img.save(os.path.join(outdir, os.path.basename(jpgfile)))
    except Exception as e:
        print(e)


def image2npy(npy_path='D:\\dataset\\GTRSB', jpg_path='D:\dataset\GTRSB\Trainning_Images_Shaped_32'):
    imag_array = np.empty([39209, 32, 32], float)
    j = 0
    for i in range(0, 43):
        for jpgfile in glob.glob(jpg_path + '\\' + format(i, '05d') + r'\\*.jpg'):
            img = Image.open(jpgfile)
            imag_array[j] = np.array(img) / 255
            j = j + 1
        print(format(i, '05d') + "done")
    np.save(npy_path + "\\imag.npy", imag_array)
    print(imag_array[0].shape)


if __name__ == "__main__":
    # define dataset path
    root_path = 'D:\\dataset\\GTRSB\\'
    train_data_dir = root_path + 'GTRSB_Final_Training_Images\\GTSRB\\Final_Training\\Images'
    test_data_dir = root_path + 'GTRSB_Final_Test_Images\\GTSRB\\Final_Test\\Images'

    # create  jpg file path
    test_jpg_dir = root_path + 'GTSRB_Final_Test_Images_roi_jpg'
    os.makedirs(test_jpg_dir)
    train_jpg_dir = root_path + 'GTSRB_Final_Training_Images_roi_jpg'
    os.makedirs(train_jpg_dir)

    # convert data to jpg
    convert_test_data(test_data_dir, jpg_dir=test_jpg_dir)  # save ppm file to jpg
    convert_train_data(train_data_dir, jpg_dir=train_jpg_dir)

    # save label data as npy
    save_label_to_npy(training_path=train_data_dir, npy_path=root_path)  # save label data to npy format

    # create shaped image path (train data)
    # images are shaped to 32*32, single channel ('L')
    shaped_image_dir = root_path + 'Training_Images_Shaped_32'
    os.makedirs(shaped_image_dir)
    for i in range(0, 43):
        for jpgfile in glob.glob(train_jpg_dir + '\\' + format(i, '05d') + r'\\*.jpg'):
            convertRGB2L(jpgfile, shaped_image_dir + '\\' + format(i, '05d'))

    image2npy(npy_path=root_path, jpg_path=shaped_image_dir)
