
#include <HellfireControl/Math/Math.hpp>

namespace Math {
	HC_INLINE float Clamp(float _fVal, float _fMin, float _fMax) { return _fVal > _fMax ? _fMax : (_fVal < _fMin ? _fMin : _fVal); }
	HC_INLINE Vec2F Clamp(const Vec2F& _vVal, const Vec2F& _vMin, const Vec2F& _vMax) { return Min(Max(_vVal, _vMax), _vMin); }
	HC_INLINE Vec3F Clamp(const Vec3F& _vVector, const Vec3F& _vMin, const Vec3F& _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
	HC_INLINE Vec4F Clamp(const Vec4F& _vVector, const Vec4F& _vMin, const Vec4F& _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
	HC_INLINE QuaternionF Clamp(const QuaternionF& _qVal, const QuaternionF& _qMin, const QuaternionF& _qMax) { return Clamp(_qVal.m_vQuat, _qMin.m_vQuat, _qMax.m_vQuat); }
	HC_INLINE MatrixF Clamp(const MatrixF& _mVal, const MatrixF& _mMin, const MatrixF& _mMax) {
		return MatrixF(Clamp(_mVal[0], _mMin[0], _mMax[0]),
			Clamp(_mVal[1], _mMin[1], _mMax[1]),
			Clamp(_mVal[2], _mMin[2], _mMin[2]),
			Clamp(_mVal[3], _mMin[3], _mMax[3]));
	}

	HC_INLINE float Lerp(float _fStart, float _fEnd, float _fRatio) { return (_fEnd - _fStart) * _fRatio + _fStart; }
	HC_INLINE Vec2F Lerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE Vec3F Lerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE Vec4F Lerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) { return (_vEnd - _vStart) * _fRatio + _vStart; }
	HC_INLINE MatrixF Lerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) { return (_mEnd - _mStart) * _fRatio + _mStart; }
	HC_INLINE QuaternionF Lerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) { return (_qEnd - _qStart) * _fRatio + _qStart; }

	HC_INLINE Vec2F NLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		Vec2F vEnd = _vEnd;

		if (Dot(_vStart, _vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	HC_INLINE Vec3F NLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		Vec3F vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	HC_INLINE Vec4F NLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		Vec4F vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0f) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _fRatio));
	}

	HC_INLINE MatrixF NLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(NLerp(_mStart[0], _mEnd[0], _fRatio),
			NLerp(_mStart[1], _mEnd[1], _fRatio),
			NLerp(_mStart[2], _mEnd[2], _fRatio),
			NLerp(_mStart[3], _mEnd[3], _fRatio));
	}

	HC_INLINE QuaternionF NLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		QuaternionF qEnd = _qEnd;

		if (Dot(_qStart, _qEnd) < 0.0f) { qEnd = -qEnd; }

		return Normalize(Lerp(_qStart, qEnd, _fRatio));
	}

	HC_INLINE Vec2F SLerp(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		Vec2F vStart = Normalize(_vStart);
		Vec2F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE Vec3F SLerp(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		Vec3F vStart = Normalize(_vStart);
		Vec3F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE Vec4F SLerp(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		Vec4F vStart = Normalize(_vStart);
		Vec4F vEnd = Normalize(_vEnd);
		float fDot = Dot(vStart, vEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			vEnd = -vEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * vStart) + (fTo * vEnd);
	}

	HC_INLINE MatrixF SLerp(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(SLerp(_mStart[0], _mEnd[0], _fRatio),
			SLerp(_mStart[1], _mEnd[1], _fRatio),
			SLerp(_mStart[2], _mEnd[2], _fRatio),
			SLerp(_mStart[3], _mEnd[3], _fRatio));
	}

	HC_INLINE QuaternionF SLerp(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		QuaternionF qStart = Normalize(_qStart);
		QuaternionF qEnd = Normalize(_qEnd);
		float fDot = Dot(_qStart, qEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			qEnd = -qEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(qStart, qEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);

		return (fFrom * qStart) + (fTo * qEnd);
	}

	HC_INLINE float Wrap(float _fVal, float _fLowerBound, float _fUpperBound) {
		if (_fLowerBound > _fUpperBound) return Wrap(_fVal, _fUpperBound, _fLowerBound);
		return (_fVal >= 0.0f ? _fLowerBound : _fUpperBound) + fmodf(_fVal, _fUpperBound - _fLowerBound);
	}

	HC_INLINE Vec2F Wrap(const Vec2F& _vVal, const Vec2F& _vLowerBound, const Vec2F& _vUpperBound) {
		return Vec2F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y));
	}

	HC_INLINE Vec3F Wrap(const Vec3F& _vVal, const Vec3F& _vLowerBound, const Vec3F& _vUpperBound) {
		return Vec3F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
			Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z));
	}

	HC_INLINE Vec4F Wrap(const Vec4F& _vVal, const Vec4F& _vLowerBound, const Vec4F& _vUpperBound) {
		return Vec4F(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
			Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z),
			Wrap(_vVal.w, _vLowerBound.w, _vUpperBound.w));
	}

	HC_INLINE MatrixF Wrap(const MatrixF& _mVal, const MatrixF& _mLowerBound, const MatrixF& _mUpperBound) {
		return MatrixF(Wrap(_mVal[0], _mLowerBound[0], _mUpperBound[0]),
			Wrap(_mVal[1], _mLowerBound[1], _mUpperBound[1]),
			Wrap(_mVal[2], _mLowerBound[2], _mUpperBound[2]),
			Wrap(_mVal[3], _mLowerBound[3], _mUpperBound[3]));
	}

	HC_INLINE QuaternionF Wrap(const QuaternionF& _qVal, const QuaternionF& _qLowerBound, const QuaternionF& _qUpperBound) {
		return QuaternionF(Wrap(_qVal.m_vQuat, _qLowerBound.m_vQuat, _qUpperBound.m_vQuat));
	}

	HC_INLINE float Pow(float _fBase, float _fExp) { return powf(_fBase, _fExp); }
	HC_INLINE Vec2F Pow(const Vec2F& _vBase, float _fExp) { return Vec2F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp)); }
	HC_INLINE Vec3F Pow(const Vec3F& _vBase, float _fExp) { return Vec3F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[1], _fExp)); }
	HC_INLINE Vec4F Pow(const Vec4F& _vBase, float _fExp) { return Vec4F(Pow(_vBase[0], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[1], _fExp), Pow(_vBase[2], _fExp)); }
	HC_INLINE MatrixF Pow(const MatrixF& _mBase, float _fExp) { return MatrixF(Pow(_mBase[0], _fExp), Pow(_mBase[1], _fExp), Pow(_mBase[2], _fExp), Pow(_mBase[3], _fExp)); }
	HC_INLINE QuaternionF Pow(const QuaternionF& _qBase, float _fExp) { return Pow(_qBase.m_vQuat, _fExp); }

	HC_INLINE float Log10(float _fVal) { return log10f(_fVal); }
	HC_INLINE Vec2F Log10(const Vec2F& _vVal) { return Vec2F(Log10(_vVal[0]), Log10(_vVal[1])); }
	HC_INLINE Vec3F Log10(const Vec3F& _vVal) { return Vec3F(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2])); }
	HC_INLINE Vec4F Log10(const Vec4F& _vVal) { return Vec4F(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2]), Log10(_vVal[3])); }
	HC_INLINE MatrixF Log10(const MatrixF& _mVal) { return MatrixF(Log10(_mVal[0]), Log10(_mVal[1]), Log10(_mVal[2]), Log10(_mVal[3])); }
	HC_INLINE QuaternionF Log10(const QuaternionF& _qVal) { return Log10(_qVal.m_vQuat); }

	HC_INLINE float Log2(float _fVal) { return log2f(_fVal); }
	HC_INLINE Vec2F Log2(const Vec2F& _vVal) { return Vec2F(Log2(_vVal[0]), Log2(_vVal[1])); }
	HC_INLINE Vec3F Log2(const Vec3F& _vVal) { return Vec3F(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2])); }
	HC_INLINE Vec4F Log2(const Vec4F& _vVal) { return Vec4F(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2]), Log2(_vVal[3])); }
	HC_INLINE MatrixF Log2(const MatrixF& _mVal) { return MatrixF(Log2(_mVal[0]), Log2(_mVal[1]), Log2(_mVal[2]), Log2(_mVal[3])); }
	HC_INLINE QuaternionF Log2(const QuaternionF& _qVal) { return Log2(_qVal.m_vQuat); }

	HC_INLINE float Ln(float _fVal) { return logf(_fVal); }
	HC_INLINE Vec2F Ln(const Vec2F& _vVal) { return Vec2F(Ln(_vVal[0]), Ln(_vVal[1])); }
	HC_INLINE Vec3F Ln(const Vec3F& _vVal) { return Vec3F(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2])); }
	HC_INLINE Vec4F Ln(const Vec4F& _vVal) { return Vec4F(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2]), Ln(_vVal[3])); }
	HC_INLINE MatrixF Ln(const MatrixF& _mVal) { return MatrixF(Ln(_mVal[0]), Ln(_mVal[1]), Ln(_mVal[2]), Ln(_mVal[3])); }
	HC_INLINE QuaternionF Ln(const QuaternionF& _qVal) { return Ln(_qVal.m_vQuat); }

	HC_INLINE float Oscillate(float _fMin, float _fMax, float _fPeriod, float _fTime) {
		if (_fMax < _fMin) return Oscillate(_fMax, _fMin, _fPeriod, _fTime);

		float fAmp = (_fMax - _fMin) * 0.5f;
		float fPeriod = (HC_2PI / _fPeriod);
		float fMid = (_fMin + _fMax) * 0.5f;

		return fAmp * cosf(fPeriod * _fTime) + fMid;
	}

	HC_INLINE Vec2F Oscillate(const Vec2F& _vMin, const Vec2F& _vMax, float _fPeriod, float _fTime) {
		return Vec2F(Oscillate(_vMin[0], _vMax[0], _fPeriod, _fTime),
			Oscillate(_vMin[1], _vMax[2], _fPeriod, _fTime));
	}

	HC_INLINE Vec3F Oscillate(const Vec3F& _vMin, const Vec3F& _vMax, float _fPeriod, float _fTime) {
		return Vec3F(Oscillate(_vMin[0], _vMax[0], _fPeriod, _fTime),
			Oscillate(_vMin[1], _vMax[2], _fPeriod, _fTime),
			Oscillate(_vMin[2], _vMax[2], _fPeriod, _fTime));
	}

	HC_INLINE Vec4F Oscillate(const Vec4F& _vMin, const Vec4F& _vMax, float _fPeriod, float _fTime) {
		return Vec4F(Oscillate(_vMin[0], _vMax[0], _fPeriod, _fTime),
			Oscillate(_vMin[1], _vMax[2], _fPeriod, _fTime),
			Oscillate(_vMin[2], _vMax[2], _fPeriod, _fTime),
			Oscillate(_vMin[3], _vMax[3], _fPeriod, _fTime));
	}

	HC_INLINE MatrixF Oscillate(const MatrixF& _mMin, const MatrixF& _mMax, float _fPeriod, float _fTime) {
		return MatrixF(Oscillate(_mMin[0], _mMax[0], _fPeriod, _fTime),
			Oscillate(_mMin[1], _mMax[2], _fPeriod, _fTime),
			Oscillate(_mMin[2], _mMax[2], _fPeriod, _fTime),
			Oscillate(_mMin[3], _mMax[3], _fPeriod, _fTime));
	}

	HC_INLINE QuaternionF Oscillate(const QuaternionF& _qMin, const QuaternionF& _qMax, float _fPeriod, float _fTime) {
		return Oscillate(_qMin.m_vQuat, _qMax.m_vQuat, _fPeriod, _fTime);
	}

	HC_INLINE float DampedOscillate(float _fMin, float _fMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		if (_fMax < _fMin) return DampedOscillate(_fMax, _fMin, _fPeriod, _fTime, _fDampingFactor);

		float fAmp = ((_fMax - _fMin) * 0.5f) * expf(-(_fDampingFactor)*_fTime);
		float fPeriod = HC_2PI / _fPeriod;
		float fMid = (_fMax + _fMin) * 0.5f;

		return fAmp * cosf(fPeriod * _fTime) + fMid;
	}

	HC_INLINE Vec2F DampedOscillate(const Vec2F& _vMin, const Vec2F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return Vec2F(DampedOscillate(_vMin[0], _vMax[0], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _fPeriod, _fTime, _fDampingFactor));
	}

	HC_INLINE Vec3F DampedOscillate(const Vec3F& _vMin, const Vec3F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return Vec3F(DampedOscillate(_vMin[0], _vMax[0], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[2], _vMax[2], _fPeriod, _fTime, _fDampingFactor));
	}

	HC_INLINE Vec4F DampedOscillate(const Vec4F& _vMin, const Vec4F& _vMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return Vec4F(DampedOscillate(_vMin[0], _vMax[0], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[2], _vMax[2], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_vMin[3], _vMax[3], _fPeriod, _fTime, _fDampingFactor));
	}

	HC_INLINE MatrixF DampedOscillate(const MatrixF& _mMin, const MatrixF& _mMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return MatrixF(DampedOscillate(_mMin[0], _mMax[0], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_mMin[1], _mMax[1], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_mMin[2], _mMax[2], _fPeriod, _fTime, _fDampingFactor),
			DampedOscillate(_mMin[3], _mMax[3], _fPeriod, _fTime, _fDampingFactor));
	}

	HC_INLINE QuaternionF DampedOscillate(const QuaternionF& _qMin, const QuaternionF& _qMax, float _fPeriod, float _fTime, float _fDampingFactor = 0.2f) {
		return DampedOscillate(_qMin.m_vQuat, _qMax.m_vQuat, _fPeriod, _fTime, _fDampingFactor);
	}

	HC_INLINE float SmoothStep(float _fStart, float _fEnd, float _fRatio) {
		_fRatio = Clamp(_fRatio);
		_fRatio = _fRatio * _fRatio * (3.0f - (2.0f * _fRatio));
		return _fEnd * _fRatio + _fStart * (1.0f - _fRatio);
	}

	HC_INLINE Vec2F SmoothStep(const Vec2F& _vStart, const Vec2F& _vEnd, float _fRatio) {
		return Vec2F(SmoothStep(_vStart[0], _vEnd[0], _fRatio),
			SmoothStep(_vStart[1], _vEnd[1], _fRatio));
	}

	HC_INLINE Vec3F SmoothStep(const Vec3F& _vStart, const Vec3F& _vEnd, float _fRatio) {
		return Vec3F(SmoothStep(_vStart[0], _vEnd[0], _fRatio),
			SmoothStep(_vStart[1], _vEnd[1], _fRatio),
			SmoothStep(_vStart[2], _vEnd[2], _fRatio));
	}

	HC_INLINE Vec4F SmoothStep(const Vec4F& _vStart, const Vec4F& _vEnd, float _fRatio) {
		return Vec4F(SmoothStep(_vStart[0], _vEnd[0], _fRatio),
			SmoothStep(_vStart[1], _vEnd[1], _fRatio),
			SmoothStep(_vStart[2], _vEnd[2], _fRatio),
			SmoothStep(_vStart[3], _vEnd[3], _fRatio));
	}

	HC_INLINE MatrixF SmoothStep(const MatrixF& _mStart, const MatrixF& _mEnd, float _fRatio) {
		return MatrixF(SmoothStep(_mStart[0], _mEnd[0], _fRatio),
			SmoothStep(_mStart[1], _mEnd[1], _fRatio),
			SmoothStep(_mStart[2], _mEnd[2], _fRatio),
			SmoothStep(_mStart[3], _mEnd[3], _fRatio));
	}

	HC_INLINE QuaternionF SmoothStep(const QuaternionF& _qStart, const QuaternionF& _qEnd, float _fRatio) {
		return SmoothStep(_qStart.m_vQuat, _qEnd.m_vQuat, _fRatio);
	}

	HC_INLINE float DampedSmoothStep(float _fCurrent, float _fGoal, float& _fVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		float fOmega = 2.0f / _fSmoothTime;
		float fX = fOmega * _fTimeDelta;
		float fExponent = 1.0f / (1.0f * fX + ((fX * fX) * (0.48f + 0.235f * fX)));
		float fDeltaCap = _fMaxChange * _fSmoothTime;

		float fChange = _fCurrent - _fGoal;
		fChange = Clamp(fChange, -fDeltaCap, fDeltaCap);

		float fTemp = (_fVelocity + fOmega * fChange) * _fTimeDelta;
		_fVelocity = (_fVelocity - fOmega * fTemp) * fExponent;

		return _fGoal + (fChange + fTemp) * fExponent;
	}

	HC_INLINE Vec2F DampedSmoothStep(const Vec2F& _vCurrent, const Vec2F& _vGoal, Vec2F& _vVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		float fOmega = 2.0f / _fSmoothTime;
		float fX = fOmega * _fTimeDelta;
		float fExponent = 1.0f / (1.0f * fX + ((fX * fX) * (0.48f + 0.235f * fX)));
		float fDeltaCap = _fMaxChange * _fSmoothTime;

		Vec2F vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec2F(-fDeltaCap), Vec2F(fDeltaCap));

		Vec2F vTemp = (_vVelocity + Vec2F(fOmega) * vChange) * _fTimeDelta;
		_vVelocity = (_vVelocity - Vec2F(fOmega) * vTemp) * fExponent;

		return _vGoal + (vChange + vTemp) * fExponent;
	}

	HC_INLINE Vec3F DampedSmoothStep(const Vec3F& _vCurrent, const Vec3F& _vGoal, Vec3F& _vVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		float fOmega = 2.0f / _fSmoothTime;
		float fX = fOmega * _fTimeDelta;
		float fExponent = 1.0f / (1.0f * fX + ((fX * fX) * (0.48f + 0.235f * fX)));
		float fDeltaCap = _fMaxChange * _fSmoothTime;

		Vec3F vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec3F(-fDeltaCap), Vec3F(fDeltaCap));

		Vec3F vTemp = (_vVelocity + Vec3F(fOmega) * vChange) * _fTimeDelta;
		_vVelocity = (_vVelocity - Vec3F(fOmega) * vTemp) * fExponent;

		return _vGoal + (vChange + vTemp) * fExponent;
	}

	HC_INLINE Vec4F DampedSmoothStep(const Vec4F& _vCurrent, const Vec4F& _vGoal, Vec4F& _vVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		float fOmega = 2.0f / _fSmoothTime;
		float fX = fOmega * _fTimeDelta;
		float fExponent = 1.0f / (1.0f * fX + ((fX * fX) * (0.48f + 0.235f * fX)));
		float fDeltaCap = _fMaxChange * _fSmoothTime;

		Vec4F vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec4F(-fDeltaCap), Vec4F(fDeltaCap));

		Vec4F vTemp = (_vVelocity + Vec4F(fOmega) * vChange) * _fTimeDelta;
		_vVelocity = (_vVelocity - Vec4F(fOmega) * vTemp) * fExponent;

		return _vGoal + (vChange + vTemp) * fExponent;
	}

	HC_INLINE MatrixF DampedSmoothStep(const MatrixF& _mCurrent, const MatrixF& _mGoal, MatrixF& _mVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		return MatrixF(DampedSmoothStep(_mCurrent[0], _mGoal[0], _mVelocity[0], _fTimeDelta, _fSmoothTime, _fMaxChange),
			DampedSmoothStep(_mCurrent[1], _mGoal[1], _mVelocity[1], _fTimeDelta, _fSmoothTime, _fMaxChange),
			DampedSmoothStep(_mCurrent[2], _mGoal[2], _mVelocity[2], _fTimeDelta, _fSmoothTime, _fMaxChange),
			DampedSmoothStep(_mCurrent[3], _mGoal[3], _mVelocity[3], _fTimeDelta, _fSmoothTime, _fMaxChange));
	}

	HC_INLINE QuaternionF DampedSmoothStep(const QuaternionF& _qCurrent, const QuaternionF& _qGoal, QuaternionF& _qVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		return DampedSmoothStep(_qCurrent.m_vQuat, _qGoal.m_vQuat, _qVelocity.m_vQuat, _fTimeDelta, _fSmoothTime, _fMaxChange);
	}

	HC_INLINE float InverseSmoothStep(float _fVal) {
		_fVal = Clamp(_fVal);
		return 0.5f - sinf(asinf(1.0f - 2.0f * _fVal) / 3.0f);
	}

	HC_INLINE Vec2F InverseSmoothStep(const Vec2F& _vVal) {
		return Vec2F(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]));
	}

	HC_INLINE Vec3F InverseSmoothStep(const Vec3F& _vVal) {
		return Vec3F(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]),
			InverseSmoothStep(_vVal[2]));
	}

	HC_INLINE Vec4F InverseSmoothStep(const Vec4F& _vVal) {
		return Vec4F(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]),
			InverseSmoothStep(_vVal[2]),
			InverseSmoothStep(_vVal[3]));
	}

	HC_INLINE MatrixF InverseSmoothStep(const MatrixF& _mVal) {
		return MatrixF(InverseSmoothStep(_mVal[0]),
			InverseSmoothStep(_mVal[1]),
			InverseSmoothStep(_mVal[2]),
			InverseSmoothStep(_mVal[3]));
	}

	HC_INLINE QuaternionF InverseSmoothStep(const QuaternionF& _qVal) {
		return InverseSmoothStep(_qVal.m_vQuat);
	}

#if HC_ENABLE_DOUBLE_PRECISION
	HC_INLINE double Clamp(double _dVal, double _dMin, double _dMax) { return _dVal > _dMax ? _dMax : (_dVal < _dMin ? _dMin : _dVal); }
	HC_INLINE Vec2D Clamp(const Vec2D& _vVal, const Vec2D& _vMin, const Vec2D& _vMax) { return Min(Max(_vVal, _vMax), _vMin); }
	HC_INLINE Vec3D Clamp(const Vec3D& _vVector, const Vec3D& _vMin, const Vec3D& _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
	HC_INLINE Vec4D Clamp(const Vec4D& _vVector, const Vec4D& _vMin, const Vec4D& _vMax) { return Min(Max(_vVector, _vMax), _vMin); }
	HC_INLINE QuaternionD Clamp(const QuaternionD& _qVal, const QuaternionD& _qMin, const QuaternionD& _qMax) { return Clamp(_qVal.m_vQuat, _qMin.m_vQuat, _qMax.m_vQuat); }
	HC_INLINE MatrixD Clamp(const MatrixD& _mVal, const MatrixD& _mMin, const MatrixD& _mMax) {
		return MatrixD(Clamp(_mVal[0], _mMin[0], _mMax[0]),
			Clamp(_mVal[1], _mMin[1], _mMax[1]),
			Clamp(_mVal[2], _mMin[2], _mMin[2]),
			Clamp(_mVal[3], _mMin[3], _mMax[3]));
	}

	HC_INLINE double Lerp(double _dStart, double _dEnd, double _dRatio) { return (_dEnd - _dStart) * _dRatio + _dStart; }
	HC_INLINE Vec2D Lerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE Vec3D Lerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE Vec4D Lerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) { return (_vEnd - _vStart) * _dRatio + _vStart; }
	HC_INLINE MatrixD Lerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) { return (_mEnd - _mStart) * _dRatio + _mStart; }
	HC_INLINE QuaternionD Lerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) { return (_qEnd - _qStart) * _dRatio + _qStart; }

	HC_INLINE Vec2D NLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		Vec2D vEnd = _vEnd;

		if (Dot(_vStart, _vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	HC_INLINE Vec3D NLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		Vec3D vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	HC_INLINE Vec4D NLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		Vec4D vEnd = _vEnd;

		if (Dot(_vStart, vEnd) < 0.0) { vEnd = -vEnd; }

		return Normalize(Lerp(_vStart, vEnd, _dRatio));
	}

	HC_INLINE MatrixD NLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(NLerp(_mStart[0], _mEnd[0], _dRatio),
			NLerp(_mStart[1], _mEnd[1], _dRatio),
			NLerp(_mStart[2], _mEnd[2], _dRatio),
			NLerp(_mStart[3], _mEnd[3], _dRatio));
	}

	HC_INLINE QuaternionD NLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		QuaternionD qEnd = _qEnd;

		if (Dot(_qStart, _qEnd) < 0.0) { qEnd = -qEnd; }

		return Normalize(Lerp(_qStart, qEnd, _dRatio));
	}

	HC_INLINE Vec2D SLerp(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		Vec2D vStart = Normalize(_vStart);
		Vec2D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE Vec3D SLerp(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		Vec3D vStart = Normalize(_vStart);
		Vec3D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE Vec4D SLerp(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		Vec4D vStart = Normalize(_vStart);
		Vec4D vEnd = Normalize(_vEnd);
		double dDot = Dot(vStart, vEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			vEnd = -vEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(vStart, vEnd, _dRatio); }

		double dTheta = acosf(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * vStart) + (dTo * vEnd);
	}

	HC_INLINE MatrixD SLerp(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(SLerp(_mStart[0], _mEnd[0], _dRatio),
			SLerp(_mStart[1], _mEnd[1], _dRatio),
			SLerp(_mStart[2], _mEnd[2], _dRatio),
			SLerp(_mStart[3], _mEnd[3], _dRatio));
	}

	HC_INLINE QuaternionD SLerp(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		QuaternionD qStart = Normalize(_qStart);
		QuaternionD qEnd = Normalize(_qEnd);
		double dDot = Dot(_qStart, qEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			qEnd = -qEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(qStart, qEnd, _dRatio); }

		double dTheta = acos(dDot);
		double dFrom = sin((1.0f - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);

		return (dFrom * qStart) + (dTo * qEnd);
	}

	HC_INLINE double Wrap(double _dVal, double _dLowerBound, double _dUpperBound) {
		if (_dLowerBound > _dUpperBound) return Wrap(_dVal, _dUpperBound, _dLowerBound);
		return (_dVal >= 0.0 ? _dLowerBound : _dUpperBound) + fmod(_dVal, _dUpperBound - _dLowerBound);
	}

	HC_INLINE Vec2D Wrap(const Vec2D& _vVal, const Vec2D& _vLowerBound, const Vec2D& _vUpperBound) {
		return Vec2D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y));
	}

	HC_INLINE Vec3D Wrap(const Vec3D& _vVal, const Vec3D& _vLowerBound, const Vec3D& _vUpperBound) {
		return Vec3D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
			Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z));
	}

	HC_INLINE Vec4D Wrap(const Vec4D& _vVal, const Vec4D& _vLowerBound, const Vec4D& _vUpperBound) {
		return Vec4D(Wrap(_vVal.x, _vLowerBound.x, _vUpperBound.y),
			Wrap(_vVal.y, _vLowerBound.y, _vUpperBound.y),
			Wrap(_vVal.z, _vLowerBound.z, _vUpperBound.z),
			Wrap(_vVal.w, _vLowerBound.w, _vUpperBound.w));
	}

	HC_INLINE MatrixD Wrap(const MatrixD& _mVal, const MatrixD& _mLowerBound, const MatrixD& _mUpperBound) {
		return MatrixD(Wrap(_mVal[0], _mLowerBound[0], _mUpperBound[0]),
			Wrap(_mVal[1], _mLowerBound[1], _mUpperBound[1]),
			Wrap(_mVal[2], _mLowerBound[2], _mUpperBound[2]),
			Wrap(_mVal[3], _mLowerBound[3], _mUpperBound[3]));
	}

	HC_INLINE QuaternionD Wrap(const QuaternionD& _qVal, const QuaternionD& _qLowerBound, const QuaternionD& _qUpperBound) {
		return QuaternionD(Wrap(_qVal.m_vQuat, _qLowerBound.m_vQuat, _qUpperBound.m_vQuat));
	}

	HC_INLINE double Pow(double _dBase, double _dExp) { return pow(_dBase, _dExp); }
	HC_INLINE Vec2D Pow(const Vec2D& _vBase, double _dExp) { return Vec2D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp)); }
	HC_INLINE Vec3D Pow(const Vec3D& _vBase, double _dExp) { return Vec3D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp), Pow(_vBase[2], _dExp)); }
	HC_INLINE Vec4D Pow(const Vec4D& _vBase, double _dExp) { return Vec4D(Pow(_vBase[0], _dExp), Pow(_vBase[1], _dExp), Pow(_vBase[2], _dExp), Pow(_vBase[3], _dExp)); }
	HC_INLINE MatrixD Pow(const MatrixD& _mBase, double _dExp) { return MatrixD(Pow(_mBase[0], _dExp), Pow(_mBase[1], _dExp), Pow(_mBase[2], _dExp), Pow(_mBase[3], _dExp)); }
	HC_INLINE QuaternionD Pow(const QuaternionD& _qBase, double _dExp) { return Pow(_qBase.m_vQuat, _dExp); }

	HC_INLINE double Log10(double _dVal) { return log10(_dVal); }
	HC_INLINE Vec2D Log10(const Vec2D& _vVal) { return Vec2D(Log10(_vVal[0]), Log10(_vVal[1])); }
	HC_INLINE Vec3D Log10(const Vec3D& _vVal) { return Vec3D(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2])); }
	HC_INLINE Vec4D Log10(const Vec4D& _vVal) { return Vec4D(Log10(_vVal[0]), Log10(_vVal[1]), Log10(_vVal[2]), Log10(_vVal[3])); }
	HC_INLINE MatrixD Log10(const MatrixD& _mVal) { return MatrixD(Log10(_mVal[0]), Log10(_mVal[1]), Log10(_mVal[2]), Log10(_mVal[3])); }
	HC_INLINE QuaternionD Log10(const QuaternionD& _qVal) { return Log10(_qVal.m_vQuat); }

	HC_INLINE double Log2(double _dVal) { return log2(_dVal); }
	HC_INLINE Vec2D Log2(const Vec2D& _vVal) { return Vec2D(Log2(_vVal[0]), Log2(_vVal[1])); }
	HC_INLINE Vec3D Log2(const Vec3D& _vVal) { return Vec3D(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2])); }
	HC_INLINE Vec4D Log2(const Vec4D& _vVal) { return Vec4D(Log2(_vVal[0]), Log2(_vVal[1]), Log2(_vVal[2]), Log2(_vVal[3])); }
	HC_INLINE MatrixD Log2(const MatrixD& _mVal) { return MatrixD(Log2(_mVal[0]), Log2(_mVal[1]), Log2(_mVal[2]), Log2(_mVal[3])); }
	HC_INLINE QuaternionD Log2(const QuaternionD& _qVal) { return Log2(_qVal.m_vQuat); }

	HC_INLINE double Ln(double _dVal) { return log(_dVal); }
	HC_INLINE Vec2D Ln(const Vec2D& _vVal) { return Vec2D(Ln(_vVal[0]), Ln(_vVal[1])); }
	HC_INLINE Vec3D Ln(const Vec3D& _vVal) { return Vec3D(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2])); }
	HC_INLINE Vec4D Ln(const Vec4D& _vVal) { return Vec4D(Ln(_vVal[0]), Ln(_vVal[1]), Ln(_vVal[2]), Ln(_vVal[3])); }
	HC_INLINE MatrixD Ln(const MatrixD& _mVal) { return MatrixD(Ln(_mVal[0]), Ln(_mVal[1]), Ln(_mVal[2]), Ln(_mVal[3])); }
	HC_INLINE QuaternionD Ln(const QuaternionD& _qVal) { return Ln(_qVal.m_vQuat); }

	HC_INLINE double Oscillate(double _dMin, double _dMax, double _dPeriod, double _dTime) {
		if (_dMax < _dMin) return Oscillate(_dMax, _dMin, _dPeriod, _dTime);

		double dAmp = (_dMax - _dMin) * 0.5;
		double dPeriod = (HC_2PI / _dPeriod);
		double dMid = (_dMin + _dMax) * 0.5;

		return dAmp * cos(dPeriod * _dTime) + dMid;
	}

	HC_INLINE Vec2D Oscillate(const Vec2D& _vMin, const Vec2D& _vMax, double _dPeriod, double _dTime) {
		return Vec2D(Oscillate(_vMin[0], _vMax[0], _dPeriod, _dTime),
			Oscillate(_vMin[1], _vMax[2], _dPeriod, _dTime));
	}

	HC_INLINE Vec3D Oscillate(const Vec3D& _vMin, const Vec3D& _vMax, double _dPeriod, double _dTime) {
		return Vec3D(Oscillate(_vMin[0], _vMax[0], _dPeriod, _dTime),
			Oscillate(_vMin[1], _vMax[2], _dPeriod, _dTime),
			Oscillate(_vMin[2], _vMax[2], _dPeriod, _dTime));
	}

	HC_INLINE Vec4D Oscillate(const Vec4D& _vMin, const Vec4D& _vMax, double _dPeriod, double _dTime) {
		return Vec4D(Oscillate(_vMin[0], _vMax[0], _dPeriod, _dTime),
			Oscillate(_vMin[1], _vMax[2], _dPeriod, _dTime),
			Oscillate(_vMin[2], _vMax[2], _dPeriod, _dTime),
			Oscillate(_vMin[3], _vMax[3], _dPeriod, _dTime));
	}

	HC_INLINE MatrixD Oscillate(const MatrixD& _mMin, const MatrixD& _mMax, double _dPeriod, double _dTime) {
		return MatrixD(Oscillate(_mMin[0], _mMax[0], _dPeriod, _dTime),
			Oscillate(_mMin[1], _mMax[2], _dPeriod, _dTime),
			Oscillate(_mMin[2], _mMax[2], _dPeriod, _dTime),
			Oscillate(_mMin[3], _mMax[3], _dPeriod, _dTime));
	}

	HC_INLINE QuaternionD Oscillate(const QuaternionD& _qMin, const QuaternionD& _qMax, double _dPeriod, double _dTime) {
		return Oscillate(_qMin.m_vQuat, _qMax.m_vQuat, _dPeriod, _dTime);
	}

	HC_INLINE double DampedOscillate(double _dMin, double _dMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		if (_dMax < _dMin) return DampedOscillate(_dMax, _dMin, _dPeriod, _dTime, _dDampingFactor);

		double dAmp = ((_dMax - _dMin) * 0.5) * exp(-(_dDampingFactor)*_dTime);
		double dPeriod = HC_2PI / _dPeriod;
		double dMid = (_dMax + _dMin) * 0.5;

		return dAmp * cos(dPeriod * _dTime) + dMid;
	}

	HC_INLINE Vec2D DampedOscillate(const Vec2D& _vMin, const Vec2D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return Vec2D(DampedOscillate(_vMin[0], _vMax[0], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _dPeriod, _dTime, _dDampingFactor));
	}

	HC_INLINE Vec3D DampedOscillate(const Vec3D& _vMin, const Vec3D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return Vec3D(DampedOscillate(_vMin[0], _vMax[0], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[2], _vMin[2], _dPeriod, _dTime, _dDampingFactor));
	}

	HC_INLINE Vec4D DampedOscillate(const Vec4D& _vMin, const Vec4D& _vMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return Vec4D(DampedOscillate(_vMin[0], _vMax[0], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[1], _vMax[1], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[2], _vMin[2], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_vMin[3], _vMin[3], _dPeriod, _dTime, _dDampingFactor));
	}

	HC_INLINE MatrixD DampedOscillate(const MatrixD& _mMin, const MatrixD& _mMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return MatrixD(DampedOscillate(_mMin[0], _mMax[0], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_mMin[1], _mMax[1], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_mMin[2], _mMin[2], _dPeriod, _dTime, _dDampingFactor),
			DampedOscillate(_mMin[3], _mMin[3], _dPeriod, _dTime, _dDampingFactor));
	}

	HC_INLINE QuaternionD DampedOscillate(const QuaternionD& _qMin, const QuaternionD& _qMax, double _dPeriod, double _dTime, double _dDampingFactor = 0.2) {
		return DampedOscillate(_qMin.m_vQuat, _qMax.m_vQuat, _dPeriod, _dTime, _dDampingFactor);
	}

	HC_INLINE double SmoothStep(double _dStart, double _dEnd, double _dRatio) {
		_dRatio = Clamp(_dRatio);
		_dRatio = _dRatio * _dRatio * (3.0 - (2.0 * _dRatio));
		return _dEnd * _dRatio + _dStart * (1.0 - _dRatio);
	}

	HC_INLINE Vec2D SmoothStep(const Vec2D& _vStart, const Vec2D& _vEnd, double _dRatio) {
		return Vec2D(SmoothStep(_vStart[0], _vEnd[0], _dRatio),
			SmoothStep(_vStart[1], _vEnd[1], _dRatio));
	}

	HC_INLINE Vec3D SmoothStep(const Vec3D& _vStart, const Vec3D& _vEnd, double _dRatio) {
		return Vec3D(SmoothStep(_vStart[0], _vEnd[0], _dRatio),
			SmoothStep(_vStart[1], _vEnd[1], _dRatio),
			SmoothStep(_vStart[2], _vEnd[2], _dRatio));
	}

	HC_INLINE Vec4D SmoothStep(const Vec4D& _vStart, const Vec4D& _vEnd, double _dRatio) {
		return Vec4D(SmoothStep(_vStart[0], _vEnd[0], _dRatio),
			SmoothStep(_vStart[1], _vEnd[1], _dRatio),
			SmoothStep(_vStart[2], _vEnd[2], _dRatio),
			SmoothStep(_vStart[3], _vEnd[3], _dRatio));
	}

	HC_INLINE MatrixD SmoothStep(const MatrixD& _mStart, const MatrixD& _mEnd, double _dRatio) {
		return MatrixD(SmoothStep(_mStart[0], _mEnd[0], _dRatio),
			SmoothStep(_mStart[1], _mEnd[1], _dRatio),
			SmoothStep(_mStart[2], _mEnd[2], _dRatio),
			SmoothStep(_mStart[3], _mEnd[3], _dRatio));
	}

	HC_INLINE QuaternionD SmoothStep(const QuaternionD& _qStart, const QuaternionD& _qEnd, double _dRatio) {
		return SmoothStep(_qStart.m_vQuat, _qEnd.m_vQuat, _dRatio);
	}

	HC_INLINE double DampedSmoothStep(double _dCurrent, double _dGoal, double& _dVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		double dOmega = 2.0 / _dSmoothTime;
		double dX = dOmega * _dTimeDelta;
		double dExponent = 1.0 / (1.0 * dX + ((dX * dX) * (0.48f + 0.235f * dX)));
		double dDeltaCap = _dMaxChange * _dSmoothTime;

		double dChange = _dCurrent - _dGoal;
		dChange = Clamp(dChange, -dDeltaCap, dDeltaCap);

		double dTemp = (_dVelocity + dOmega * dChange) * _dTimeDelta;
		_dVelocity = (_dVelocity - dOmega * dTemp) * dExponent;

		return _dGoal + (dChange + dTemp) * dExponent;
	}

	HC_INLINE Vec2D DampedSmoothStep(const Vec2D& _vCurrent, const Vec2D& _vGoal, Vec2D& _vVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		double dOmega = 2.0 / _dSmoothTime;
		double dX = dOmega * _dTimeDelta;
		double dExponent = 1.0 / (1.0 * dX + ((dX * dX) * (0.48 + 0.235 * dX)));
		double dDeltaCap = _dMaxChange * _dSmoothTime;

		Vec2D vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec2D(-dDeltaCap), Vec2D(dDeltaCap));

		Vec2D vTemp = (_vVelocity + Vec2D(dOmega) * vChange) * _dTimeDelta;
		_vVelocity = (_vVelocity - Vec2D(dOmega) * vTemp) * dExponent;

		return _vGoal + (vChange + vTemp) * dExponent;
	}

	HC_INLINE Vec3D DampedSmoothStep(const Vec3D& _vCurrent, const Vec3D& _vGoal, Vec3D& _vVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		double dOmega = 2.0 / _dSmoothTime;
		double dX = dOmega * _dTimeDelta;
		double dExponent = 1.0 / (1.0 * dX + ((dX * dX) * (0.48 + 0.235 * dX)));
		double dDeltaCap = _dMaxChange * _dSmoothTime;

		Vec3D vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec3D(-dDeltaCap), Vec3D(dDeltaCap));

		Vec3D vTemp = (_vVelocity + Vec3D(dOmega) * vChange) * _dTimeDelta;
		_vVelocity = (_vVelocity - Vec3D(dOmega) * vTemp) * dExponent;

		return _vGoal + (vChange + vTemp) * dExponent;
	}

	HC_INLINE Vec4D DampedSmoothStep(const Vec4D& _vCurrent, const Vec4D& _vGoal, Vec4D& _vVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		double dOmega = 2.0 / _dSmoothTime;
		double dX = dOmega * _dTimeDelta;
		double dExponent = 1.0 / (1.0 * dX + ((dX * dX) * (0.48 + 0.235 * dX)));
		double dDeltaCap = _dMaxChange * _dSmoothTime;

		Vec4D vChange = _vCurrent - _vGoal;
		vChange = Clamp(vChange, Vec4D(-dDeltaCap), Vec4D(dDeltaCap));

		Vec4D vTemp = (_vVelocity + Vec4D(dOmega) * vChange) * _dTimeDelta;
		_vVelocity = (_vVelocity - Vec4D(dOmega) * vTemp) * dExponent;

		return _vGoal + (vChange + vTemp) * dExponent;
	}

	HC_INLINE MatrixD DampedSmoothStep(const MatrixD& _mCurrent, const MatrixD& _mGoal, MatrixD& _mVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		return MatrixD(DampedSmoothStep(_mCurrent[0], _mGoal[0], _mVelocity[0], _dTimeDelta, _dSmoothTime, _dMaxChange),
			DampedSmoothStep(_mCurrent[1], _mGoal[1], _mVelocity[1], _dTimeDelta, _dSmoothTime, _dMaxChange),
			DampedSmoothStep(_mCurrent[2], _mGoal[2], _mVelocity[2], _dTimeDelta, _dSmoothTime, _dMaxChange),
			DampedSmoothStep(_mCurrent[3], _mGoal[3], _mVelocity[3], _dTimeDelta, _dSmoothTime, _dMaxChange));
	}

	HC_INLINE QuaternionD DampedSmoothStep(const QuaternionD& _qCurrent, const QuaternionD& _qGoal, QuaternionD& _qVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		return DampedSmoothStep(_qCurrent.m_vQuat, _qGoal.m_vQuat, _qVelocity.m_vQuat, _dTimeDelta, _dSmoothTime, _dMaxChange);
	}

	HC_INLINE double InverseSmoothStep(double _dVal) {
		_dVal = Clamp(_dVal);
		return 0.5 - sin(asin(1.0 - 2.0 * _dVal) / 3.0);
	}

	HC_INLINE Vec2D InverseSmoothStep(const Vec2D& _vVal) {
		return Vec2D(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]));
	}

	HC_INLINE Vec3D InverseSmoothStep(const Vec3D& _vVal) {
		return Vec3D(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]),
			InverseSmoothStep(_vVal[2]));
	}

	HC_INLINE Vec4D InverseSmoothStep(const Vec4D& _vVal) {
		return Vec4D(InverseSmoothStep(_vVal[0]),
			InverseSmoothStep(_vVal[1]),
			InverseSmoothStep(_vVal[2]),
			InverseSmoothStep(_vVal[3]));
	}

	HC_INLINE MatrixD InverseSmoothStep(const MatrixD& _mVal) {
		return MatrixD(InverseSmoothStep(_mVal[0]),
			InverseSmoothStep(_mVal[1]),
			InverseSmoothStep(_mVal[2]),
			InverseSmoothStep(_mVal[3]));
	}

	HC_INLINE QuaternionD InverseSmoothStep(const QuaternionD& _qVal) {
		return InverseSmoothStep(_qVal.m_vQuat);
	}
#endif

#if HC_USE_ROTOR
	HC_INLINE RotorF Clamp(const RotorF& _rVal, const RotorF& _rMin, const RotorF& _rMax) { return Clamp(_rVal.m_vRot, _rMin.m_vRot, _rMax.m_vRot); }

	HC_INLINE RotorF Lerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) { return RotorF(Lerp(_rStart.m_vRot, _rEnd.m_vRot, _fRatio)); }

	HC_INLINE RotorF NLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		RotorF rEnd = _rEnd;

		if (Dot(_rStart, _rEnd)) { rEnd = -rEnd; }

		return Normalize(Lerp(_rStart, rEnd, _fRatio));
	}

	HC_INLINE RotorF SLerp(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		RotorF rStart = _rStart;
		RotorF rEnd = _rEnd;
		float fDot = Dot(_rStart, _rEnd);

		if (fDot < 0.0f) {
			fDot = -fDot;
			rEnd = -rEnd;
		}

		if (fDot > HC_NEAR_ONE) { return NLerp(rStart, rEnd, _fRatio); }

		float fTheta = acosf(fDot);
		float fFrom = sinf((1.0f - _fRatio) * fTheta) / sinf(fTheta);
		float fTo = sinf(_fRatio * fTheta) / sinf(fTheta);
		return (fFrom * rStart) + (fTo * rEnd);
	}

	HC_INLINE RotorF Wrap(const RotorF& _rVal, const RotorF& _rLowerBound, const RotorF& _rUpperBound) {
		return RotorF(Wrap(_rVal.m_vRot, _rLowerBound.m_vRot, _rUpperBound.m_vRot));
	}

	HC_INLINE RotorF Pow(const RotorF& _rBase, float _fExp) { return Pow(_rBase.m_vRot, _fExp); }

	HC_INLINE RotorF Log10(const RotorF& _rVal) { return Log10(_rVal.m_vRot); }

	HC_INLINE RotorF Log2(const RotorF& _rVal) { return Log2(_rVal.m_vRot); }

	HC_INLINE RotorF Ln(const RotorF& _rVal) { return Ln(_rVal.m_vRot); }

	HC_INLINE RotorF Oscillate(const RotorF& _rMin, const RotorF& _rMax, float _fPeriod, float _fTime) {
		return Oscillate(_rMin.m_vRot, _rMax.m_vRot, _fPeriod, _fTime);
	}

	HC_INLINE RotorF DampedOscillate(const RotorF& _rMin, const RotorF& _rMax, float _fPeriod, float _fTime, float _fDampingRatio = 0.2f) {
		return DampedOscillate(_rMin.m_vRot, _rMax.m_vRot, _fPeriod, _fTime, _fDampingRatio);
	}

	HC_INLINE RotorF SmoothStep(const RotorF& _rStart, const RotorF& _rEnd, float _fRatio) {
		return SmoothStep(_rStart.m_vRot, _rEnd.m_vRot, _fRatio);
	}

	HC_INLINE RotorF DampedSmoothStep(const RotorF& _rCurrent, const RotorF& _rGoal, RotorF& _rVelocity, float _fTimeDelta, float _fSmoothTime = 0.0001f, float _fMaxChange = FLT_MAX) {
		return DampedSmoothStep(_rCurrent.m_vRot, _rGoal.m_vRot, _rVelocity.m_vRot, _fTimeDelta, _fSmoothTime, _fMaxChange);
	}

	HC_INLINE RotorF InverseSmoothStep(const RotorF& _rVal) {
		return InverseSmoothStep(_rVal.m_vRot);
	}

#if HC_ENABLE_DOUBLE_PRECISION
	HC_INLINE RotorD Clamp(const RotorD& _rVal, const RotorD& _rMin, const RotorD& _rMax) { return Clamp(_rVal.m_vRot, _rMin.m_vRot, _rMax.m_vRot); }

	HC_INLINE RotorD Lerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) { return RotorD(Lerp(_rStart.m_vRot, _rEnd.m_vRot, _dRatio)); }

	HC_INLINE RotorD NLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		RotorD rEnd = _rEnd;

		if (Dot(_rStart, _rEnd)) { rEnd = -rEnd; }

		return Normalize(Lerp(_rStart, rEnd, _dRatio));
	}

	HC_INLINE RotorD SLerp(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		RotorD rStart = _rStart;
		RotorD rEnd = _rEnd;
		double dDot = Dot(_rStart, _rEnd);

		if (dDot < 0.0) {
			dDot = -dDot;
			rEnd = -rEnd;
		}

		if (dDot > HC_NEAR_ONE) { return NLerp(rStart, rEnd, _dRatio); }

		double dTheta = acos(dDot);
		double dFrom = sin((1.0 - _dRatio) * dTheta) / sin(dTheta);
		double dTo = sin(_dRatio * dTheta) / sin(dTheta);
		return (dFrom * rStart) + (dTo * rEnd);
	}

	HC_INLINE RotorD Wrap(const RotorD& _rVal, const RotorD& _rLowerBound, const RotorD& _rUpperBound) {
		return RotorD(Wrap(_rVal.m_vRot, _rLowerBound.m_vRot, _rUpperBound.m_vRot));
	}

	HC_INLINE RotorD Pow(const RotorD& _rBase, double _dExp) { return Pow(_rBase.m_vRot, _dExp); }

	HC_INLINE RotorD Log10(const RotorD& _rVal) { return Log10(_rVal); }

	HC_INLINE RotorD Log2(const RotorD& _rVal) { return Log2(_rVal); }

	HC_INLINE RotorD Ln(const RotorD& _rVal) { return Ln(_rVal); }

	HC_INLINE RotorD Oscillate(const RotorD& _rMin, const RotorD& _rMax, double _dPeriod, double _dTime) {
		return Oscillate(_rMin.m_vRot, _rMax.m_vRot, _dPeriod, _dTime);
	}

	HC_INLINE RotorD DampedOscillate(const RotorD& _rMin, const RotorD& _rMax, double _dPeriod, double _dTime, double _dDampingRatio = 0.2) {
		return DampedOscillate(_rMin, _rMax, _dPeriod, _dTime, _dDampingRatio);
	}

	HC_INLINE RotorD SmoothStep(const RotorD& _rStart, const RotorD& _rEnd, double _dRatio) {
		return SmoothStep(_rStart.m_vRot, _rEnd.m_vRot, _dRatio);
	}

	HC_INLINE RotorD DampedSmoothStep(const RotorD& _rCurrent, const RotorD& _rGoal, RotorD& _rVelocity, double _dTimeDelta, double _dSmoothTime = 0.0001, double _dMaxChange = DBL_MAX) {
		return DampedSmoothStep(_rCurrent.m_vRot, _rGoal.m_vRot, _rVelocity.m_vRot, _dTimeDelta, _dSmoothTime, _dMaxChange);
	}

	HC_INLINE RotorD InverseSmoothStep(const RotorD& _rVal) {
		return InverseSmoothStep(_rVal.m_vRot);
	}
#endif
#endif
}