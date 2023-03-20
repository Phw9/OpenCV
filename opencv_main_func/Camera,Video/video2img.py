import cv2
import os


video_path = "/data/stabil/test/20230130/9/test_cam2.mkv"

output_folder = "/data/stabil/test/20230130/9/images/2/"

if not os.path.exists(output_folder):
    os.makedirs(output_folder)

cap = cv2.VideoCapture(video_path)

if not cap.isOpened():
    print("Could not open video file")
    exit()

frame_count = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = int(cap.get(cv2.CAP_PROP_FPS))

for i in range(frame_count):
    # read frame
    ret, frame = cap.read()
    # if read failed break
    if not ret:
        break

    cv2.imwrite("/data/stabil/test/20230130/9/image/1/%06d.jpg", frame)

cap.release()
