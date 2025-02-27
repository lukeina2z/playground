package software.amazonaws.example;

// import com.amazonaws.xray.spring.aop.XRayEnabled;
// import org.springframework.boot.SpringApplication;
// import org.springframework.boot.autoconfigure.SpringBootApplication;
// import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;

// import jakarta.servlet.Filter;
// import org.springframework.boot.SpringApplication;
// import org.springframework.boot.autoconfigure.SpringBootApplication;
// import org.springframework.context.annotation.Bean;
// import com.amazonaws.xray.jakarta.servlet.AWSXRayServletFilter;

// import com.amazonaws.xray.spring.aop.AbstractXRayInterceptor;
// import org.aspectj.lang.annotation.Aspect;
// import org.aspectj.lang.annotation.Pointcut;
// import org.springframework.stereotype.Component;

// @SpringBootApplication(exclude={DataSourceAutoConfiguration.class})

// @Aspect
// @Component
// public class XRayInspector extends AbstractXRayInterceptor {
//     @Override
//     @Pointcut("@within(com.amazonaws.xray.spring.aop.XRayEnabled) && bean(*)")
//     public void xrayEnabledClasses() {}
// }

