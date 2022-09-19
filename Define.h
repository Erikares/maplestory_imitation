#ifndef Define_
#define Define_

#define PURE =0
#define SAFE_DELETE(p) if(p) { delete p; p = NULL;}

#define DECLARE_SINGLETONE(className)		\
private:		                            \
	static className* m_pInstance;			\
public:										\
	static className* GetInstance(void)		\
	{										\
		if(m_pInstance == NULL)				\
			m_pInstance = new className;	\
		return m_pInstance;					\
	}										\
	void DestroyInstance(void)				\
	{										\
		SAFE_DELETE(m_pInstance);			\
	}										\

#define IMPLEMENT_SINGLETONE(className)			\
	className*	className::m_pInstance = NULL;	\

#endif