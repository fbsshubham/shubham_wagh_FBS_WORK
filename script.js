
        // ===== APPLICATION STATE =====
        const AppState = {
            video: document.getElementById('camera'),
            canvas: document.getElementById('snapshot'),
            photoInput: document.getElementById('photoData'),
            photoPreview: document.getElementById('photoPreview'),
            previewImage: document.getElementById('previewImage'),
            cameraSection: document.getElementById('cameraSection'),
            captureBtn: document.getElementById('captureBtn'),
            submitBtn: document.getElementById('submitBtn'),
            stream: null,
            photoTaken: false
        };

        // ===== CAMERA HANDLER =====
        const CameraHandler = {
            async initialize() {
                try {
                    StatusHandler.show('🎥 Initializing camera...', 'info');
                    
                    const constraints = {
                        video: {
                            width: { ideal: 640 },
                            height: { ideal: 480 },
                            facingMode: 'user'
                        }
                    };

                    AppState.stream = await navigator.mediaDevices.getUserMedia(constraints);
                    AppState.video.srcObject = AppState.stream;
                    
                    AppState.video.addEventListener('loadedmetadata', () => {
                        AppState.captureBtn.disabled = false;
                        AppState.cameraSection.classList.add('active');
                        StatusHandler.show('📷 Camera ready! You can now capture your photo.', 'success');
                    });

                } catch (error) {
                    console.error('Camera access error:', error);
                    StatusHandler.show('❌ Camera access denied. Please allow camera permissions and refresh the page.', 'error');
                    this.showFallbackOption();
                }
            },

            capture() {
                if (!AppState.stream) {
                    StatusHandler.show('❌ Camera not available', 'error');
                    return;
                }

                // Set canvas dimensions to match video
                AppState.canvas.width = AppState.video.videoWidth;
                AppState.canvas.height = AppState.video.videoHeight;
                
                // Draw current video frame to canvas
                const ctx = AppState.canvas.getContext('2d');
                ctx.drawImage(AppState.video, 0, 0);
                
                // Convert to base64 (the controller expects this format)
                const photoBase64 = AppState.canvas.toDataURL('image/jpeg', 0.8);
                AppState.photoInput.value = photoBase64;
                
                // Show preview
                AppState.previewImage.src = photoBase64;
                AppState.photoPreview.style.display = 'block';
                AppState.video.style.display = 'none';
                
                AppState.photoTaken = true;
                AppState.submitBtn.disabled = false;
                AppState.captureBtn.textContent = '✅ Photo Captured';
                AppState.captureBtn.disabled = true;
                
                StatusHandler.show('✅ Photo captured successfully!', 'success');
            },

            retake() {
                AppState.photoPreview.style.display = 'none';
                AppState.video.style.display = 'block';
                AppState.photoInput.value = '';
                AppState.photoTaken = false;
                AppState.submitBtn.disabled = true;
                AppState.captureBtn.textContent = '📸 Capture Photo';
                AppState.captureBtn.disabled = false;
                
                StatusHandler.show('🔄 Ready to take a new photo', 'info');
            },

            showFallbackOption() {
                const fileInput = document.createElement('input');
                fileInput.type = 'file';
                fileInput.accept = 'image/*';
                fileInput.capture = 'camera';
                fileInput.onchange = this.handleFileSelect;
                fileInput.style.marginTop = '15px';
                
                const fallbackDiv = document.createElement('div');
                fallbackDiv.innerHTML = '<p style="color: var(--primary-color); margin-bottom: 10px;"><strong>Alternative:</strong> Upload photo from gallery</p>';
                fallbackDiv.appendChild(fileInput);
                AppState.cameraSection.appendChild(fallbackDiv);
            },

            handleFileSelect(event) {
                const file = event.target.files[0];
                if (file && file.type.startsWith('image/')) {
                    const reader = new FileReader();
                    reader.onload = function(e) {
                        AppState.photoInput.value = e.target.result;
                        AppState.previewImage.src = e.target.result;
                        AppState.photoPreview.style.display = 'block';
                        AppState.video.style.display = 'none';
                        AppState.photoTaken = true;
                        AppState.submitBtn.disabled = false;
                        StatusHandler.show('✅ Photo uploaded successfully!', 'success');
                    };
                    reader.readAsDataURL(file);
                }
            },

            cleanup() {
                if (AppState.stream) {
                    AppState.stream.getTracks().forEach(track => track.stop());
                }
            }
        };

        // ===== STATUS HANDLER =====
        const StatusHandler = {
            show(message, type) {
                const statusDiv = document.getElementById('statusMessage');
                statusDiv.className = `status-message status-${type}`;
                statusDiv.textContent = message;
                
                // Auto-hide success and info messages
                if (type === 'success' || type === 'info') {
                    setTimeout(() => {
                        statusDiv.textContent = '';
                        statusDiv.className = '';
                    }, 4000);
                }
            }
        };

        // ===== FORM HANDLER =====
        const FormHandler = {
            initialize() {
                // Form submission handler
                document.getElementById('studentForm').addEventListener('submit', this.handleSubmit);
                
                // Field validation
                const inputs = document.querySelectorAll('input[required], select[required]');
                inputs.forEach(input => {
                    input.addEventListener('blur', this.validateField);
                    input.addEventListener('input', this.validateField);
                    input.addEventListener('focus', this.handleFocus);
                    input.addEventListener('blur', this.handleBlur);
                });
            },

            handleSubmit(e) {
                if (!AppState.photoTaken) {
                    e.preventDefault();
                    StatusHandler.show('❌ Please capture a photo before submitting!', 'error');
                    return;
                }

                // Add loading state
                AppState.submitBtn.innerHTML = '<span class="loading"></span> Submitting...';
                AppState.submitBtn.disabled = true;
                
                // Form will submit normally to Spring Boot controller
                StatusHandler.show('📤 Sending data to server...', 'info');
            },

            validateField(e) {
                const field = e.target;
                if (field.value.trim() === '') {
                    field.style.borderColor = 'var(--error-color)';
                } else {
                    field.style.borderColor = 'var(--primary-color)';
                }
            },

            handleFocus(e) {
                e.target.parentElement.style.transform = 'scale(1.02)';
            },

            handleBlur(e) {
                e.target.parentElement.style.transform = 'scale(1)';
            }
        };

        // ===== GLOBAL FUNCTIONS (for HTML onclick handlers) =====
        function capturePhoto() {
            CameraHandler.capture();
        }

        function retakePhoto() {
            CameraHandler.retake();
        }

        // ===== APPLICATION INITIALIZATION =====
        document.addEventListener('DOMContentLoaded', function() {
            CameraHandler.initialize();
            FormHandler.initialize();
            
            // Set today's date as default for test date
            const today = new Date().toISOString().split('T')[0];
            document.getElementById('testDate').value = today;
        });

        // ===== CLEANUP =====
        window.addEventListener('beforeunload', function() {
            CameraHandler.cleanup();
        });
    