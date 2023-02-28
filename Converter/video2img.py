import cv2
import os


video_path = "/data/stabil/test/20230130/9/test_cam2.mkv"

output_folder = "/data/stabil/test/20230130/9/images/2/"

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

cap = cv2.VideoCapture(video_path)
print("cap")
if not cap.isOpened():
    print("Could not open video file")
    exit()

frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = int(cap.get(cv2.CAP_PROP_FPS))
print("fps")
ret = 1
count = 0
while ret:
    # read frame
    ret, frame = cap.read()
    print("read")
    # if read failed break
    if not ret:
        print("read failed")
        break
    cv2.imwrite("/data/stabil/test/20230130/9/images/2/%05d.jpg" % count, frame)
    count += 1

cap.release()
