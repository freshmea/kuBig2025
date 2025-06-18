import sys
from pathlib import Path

import cv2
import numpy as np
import torch

# YOLOv5 코드 경로 추가
ROOT = Path(__file__).resolve().parent / "yolov5"
sys.path.append(str(ROOT))

from models.common import DetectMultiBackend
from utils.augmentations import letterbox
from utils.general import non_max_suppression, scale_boxes

# 모델 로드
weights = str(ROOT / "yolov5s.pt")
device = torch.device("cpu")
model = DetectMultiBackend(weights, device=device)
imgsz = (640, 640)

# 웹캠 열기
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    img = letterbox(frame, imgsz, stride=model.stride, auto=True)[0]
    img = img[:, :, ::-1].transpose(2, 0, 1)  # BGR→RGB, HWC→CHW
    img = np.ascontiguousarray(img)
    img_tensor = torch.from_numpy(img).to(device).float() / 255.0
    img_tensor = img_tensor.unsqueeze(0)

    # 추론
    with torch.no_grad():
        pred = model(img_tensor)
        det = non_max_suppression(pred, conf_thres=0.25, iou_thres=0.45)[0]

    if det is not None and len(det):
        det[:, :4] = scale_boxes(img_tensor.shape[2:], det[:, :4], frame.shape).round()
        det = det[det[:, 4].argsort(descending=True)]

        for box in det:
            x1, y1, x2, y2 = map(int, box[:4])
            conf = float(box[4])
            cls = int(box[5])
            label = f"{model.names[cls]}: {conf:.2f}"

            # 사각형과 텍스트 표시
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.putText(
                frame,
                label,
                (x1, y1 - 10),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.6,
                (0, 0, 255),
                2,
            )
            print(f"[INFO] Detected {label} at ({x1}, {y1}, {x2}, {y2})")

    else:
        print("[INFO] No detections")

    cv2.imshow("YOLOv5 Detect", frame)
    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()
